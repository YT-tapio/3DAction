#include<vector>
#include<memory>
#include"DxLib.h"
#include"damage_ui_group.h"
#include<string>
#include"damage_ui.h"
#include<sstream>
#include<fstream>
#include<windows.h>
#include"csv_file_assistant.h"
#include"font.h"

DamageUIGroup::DamageUIGroup()
{

}

DamageUIGroup::~DamageUIGroup()
{
	player_damage_uis_.clear();
	enemy_damage_uis_.clear();
}

void DamageUIGroup::Awake()
{
	// インスタンスを生成
	for (int i = 0; i < kMaxDamageUI; i++)
	{
		player_damage_uis_.emplace_back(std::make_shared<DamageUI>("data/csv/ui/damage/player_damage_ui.csv"));
	}

	// インスタンスを生成
	for (int i = 0; i < kMaxDamageUI; i++)
	{
		enemy_damage_uis_.emplace_back(std::make_shared<DamageUI>("data/csv/ui/damage/enemy_damage_ui.csv"));
	}
}

void DamageUIGroup::Init()
{
	for (auto damage_ui : player_damage_uis_)
	{
		damage_ui->Init();
	}
}

void DamageUIGroup::Update()
{
	for (auto damage_ui : player_damage_uis_)
	{
		if (damage_ui->GetIsActive()) 
		{
			damage_ui->Update();
		}
	}
	// 敵が攻撃を受けた時描画
	for (auto damage_ui : enemy_damage_uis_)
	{
		if (damage_ui->GetIsActive())
		{
			damage_ui->Update();
		}
	}
}

const void DamageUIGroup::Draw() const
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	for (const auto damage_ui : player_damage_uis_)
	{
		if (damage_ui->GetIsActive())
		{
			damage_ui->Draw();
		}
	}
	for (const auto damage_ui : enemy_damage_uis_)
	{
		if (damage_ui->GetIsActive())
		{
			damage_ui->Draw();
		}
	}

	// 元に戻す
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
}

void DamageUIGroup::SpawnPlayerDamageUI(const VECTOR& pos,const float& damage)
{
	for (auto damage_ui : player_damage_uis_)
	{
		if (!damage_ui->GetIsActive())
		{
			damage_ui->Spawn(pos, damage);
			break;
		}
	}
}

void DamageUIGroup::SpawnEnemyDamageUI(const VECTOR& pos, const float& damage)
{
	for (auto damage_ui : enemy_damage_uis_)
	{
		if (!damage_ui->GetIsActive())
		{
			damage_ui->Spawn(pos, damage);
			break;
		}
	}
}

