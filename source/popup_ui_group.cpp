#include<vector>
#include<memory>
#include<string>
#include"DxLib.h"
#include"popup_ui_group.h"
#include"damage_ui.h"
#include<sstream>
#include<fstream>
#include<windows.h>
#include"csv_file_assistant.h"
#include"font.h"
#include"popup_ui_holder_base.h"
#include"number_popup_ui.h"
#include"image_popup_ui.h"
#include"sound_manager.h"

PopupUIGroup::PopupUIGroup()
{

}

PopupUIGroup::~PopupUIGroup()
{
	player_damage_uis_.clear();
	player_heal_uis_.clear();
	enemy_damage_uis_.clear();
	enemy_heal_uis_.clear();
	avoid_buff_uis_.clear();
}

void PopupUIGroup::Awake()
{
	int player_font_color = GetColor(255, 0, 0);
	int enemy_font_color = GetColor(0, 255, 255);
	int heal_color = GetColor(0, 255, 0);
	int edge_color = GetColor(0, 0, 0);

	// プレイヤーのインスタンスを生成
	for (int i = 0; i < kMaxDamageUI; i++)
	{
		player_damage_uis_.emplace_back(std::make_shared<NumberPopupUI>(player_font_color, edge_color));
	}
	// 敵のインスタンスを生成
	for (int i = 0; i < kMaxDamageUI; i++)
	{
		enemy_damage_uis_.emplace_back(std::make_shared<NumberPopupUI>(enemy_font_color, edge_color));
	}
	// 回復時のインスタンスを生成
	for (int i = 0; i < kMaxHealUI; i++)
	{
		enemy_heal_uis_.emplace_back(std::make_shared<NumberPopupUI>(heal_color, edge_color));
		player_heal_uis_.emplace_back(std::make_shared<NumberPopupUI>(heal_color, edge_color));
	}
	// 回避時のインスタンスを生成
	for (int i = 0; i < kMaxBuffUI; i++)
	{
		avoid_buff_uis_.emplace_back(std::make_shared<ImagePopupUI>());
	}
}

void PopupUIGroup::Init()
{
	for (auto damage_ui : player_damage_uis_)
	{
		damage_ui->Init();
	}
	for (auto damage_ui : enemy_damage_uis_)
	{
		damage_ui->Init();
	}
}

void PopupUIGroup::Update()
{
	UpdateNumberPopupUI(player_damage_uis_);
	UpdateNumberPopupUI(enemy_damage_uis_);
	UpdateNumberPopupUI(player_heal_uis_);
	UpdateNumberPopupUI(enemy_heal_uis_);
	UpdateImagePopupUI(avoid_buff_uis_);
}

const void PopupUIGroup::Draw() const
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	DrawNumberPopupUI(player_damage_uis_);
	DrawNumberPopupUI(enemy_damage_uis_);
	DrawNumberPopupUI(player_heal_uis_);
	DrawNumberPopupUI(enemy_heal_uis_);
	DrawImagePopupUI(avoid_buff_uis_);
	// 元に戻す
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
}

void PopupUIGroup::SpawnPlayerDamageUI(const VECTOR& pos,const float& damage, const bool is_critical)
{
	SpawnUI(player_damage_uis_, pos, damage, is_critical);
}

void PopupUIGroup::SpawnPlayerHealUI(const VECTOR& pos, const float& heal)
{
	SpawnUI(player_heal_uis_, pos, heal);
}

void PopupUIGroup::SpawnEnemyDamageUI(const VECTOR& pos, const float& damage, const bool is_critical)
{
	SpawnUI(enemy_damage_uis_, pos, damage, is_critical);
}

void PopupUIGroup::SpawnEnemyHealUI(const VECTOR& pos, const float& heal)
{
	SpawnUI(enemy_heal_uis_, pos, heal);
}

void PopupUIGroup::SpawnAvoidBuffUI(const VECTOR& pos, const std::string& image_name,const float& size)
{
	SpawnImagePopupUI(avoid_buff_uis_, pos, image_name, size);
}

void PopupUIGroup::UpdateNumberPopupUI(std::vector<std::shared_ptr<NumberPopupUI>> popup_uis)
{
	for (auto popup_ui : popup_uis)
	{
		if (popup_ui->GetIsActive())
		{
			popup_ui->Update();
		}
	}
}

void PopupUIGroup::UpdateImagePopupUI(std::vector<std::shared_ptr<ImagePopupUI>> popup_uis)
{
	for (auto popup_ui : popup_uis)
	{
		if (popup_ui->GetIsActive())
		{
			popup_ui->Update();
		}
	}
}

const void PopupUIGroup::DrawNumberPopupUI(std::vector<std::shared_ptr<NumberPopupUI>> popup_uis) const
{
	for (const auto popup_ui : popup_uis)
	{
		if (popup_ui->GetIsActive())
		{
			popup_ui->Draw();
		}
	}
}

const void PopupUIGroup::DrawImagePopupUI(std::vector<std::shared_ptr<ImagePopupUI>> popup_uis) const
{
	for (const auto popup_ui : popup_uis)
	{
		if (popup_ui->GetIsActive())
		{
			popup_ui->Draw();
		}
	}
}

void PopupUIGroup::SpawnUI(std::vector<std::shared_ptr<NumberPopupUI>> popup_uis, const VECTOR& pos, const float& damage, const bool is_critical)
{
	for (auto popup_ui : popup_uis)
	{
		if (!popup_ui->GetIsActive())
		{
			popup_ui->Spawn(pos, damage, is_critical);
			if (is_critical)
			{
				const std::string kCriticalHitSEName = "critical_hit";
				SoundManager::GetInstance().Play2DSound(kCriticalHitSEName);
			}
			auto test = popup_ui->GetIsActive();
			break;
		}
	}
}

void PopupUIGroup::SpawnImagePopupUI(std::vector<std::shared_ptr<ImagePopupUI>> popup_uis, const VECTOR& pos, const std::string& image_name,const float& size)
{
	for (auto popup_ui : popup_uis)
	{
		if (!popup_ui->GetIsActive())
		{
			popup_ui->Spawn(pos,image_name,size);
			auto test = popup_ui->GetIsActive();
			break;
		}
	}
}