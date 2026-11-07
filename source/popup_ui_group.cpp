#include<vector>
#include<memory>
#include"DxLib.h"
#include"popup_ui_group.h"
#include<string>
#include"damage_ui.h"
#include<sstream>
#include<fstream>
#include<windows.h>
#include"csv_file_assistant.h"
#include"font.h"
#include"number_popup_ui.h"

PopupUIGroup::PopupUIGroup()
{

}

PopupUIGroup::~PopupUIGroup()
{
	player_damage_uis_.clear();
	enemy_damage_uis_.clear();
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
	// 敵のインスタンスを生成
	for (int i = 0; i < kMaxHealUI; i++)
	{
		enemy_heal_uis_.emplace_back(std::make_shared<NumberPopupUI>(heal_color, edge_color));
		player_heal_uis_.emplace_back(std::make_shared<NumberPopupUI>(heal_color, edge_color));
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
	UpdateUI(player_damage_uis_);
	UpdateUI(enemy_damage_uis_);
	UpdateUI(player_heal_uis_);
	UpdateUI(enemy_heal_uis_);
}

const void PopupUIGroup::Draw() const
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	DrawUI(player_damage_uis_);
	DrawUI(enemy_damage_uis_);
	DrawUI(player_heal_uis_);
	DrawUI(enemy_heal_uis_);

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

void PopupUIGroup::UpdateUI(std::vector<std::shared_ptr<NumberPopupUI>> popup_uis)
{
	for (auto popup_ui : popup_uis)
	{
		if (popup_ui->GetIsActive())
		{
			popup_ui->Update();
		}
	}
}

const void PopupUIGroup::DrawUI(std::vector<std::shared_ptr<NumberPopupUI>> popup_uis) const
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
			auto test = popup_ui->GetIsActive();
			break;
		}
	}
}

