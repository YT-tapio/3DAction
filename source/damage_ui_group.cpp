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

void DamageUIGroup::Awake()
{
	// インスタンスを生成
	for (int i = 0; i < kMaxDamageUI; i++)
	{
		damage_uis_.emplace_back(std::make_shared<DamageUI>("data/csv/ui/damage/player_damage_ui.csv"));
	}
}

void DamageUIGroup::Init()
{
	for (auto damage_ui : damage_uis_)
	{
		damage_ui->Init();
	}
}

void DamageUIGroup::Update()
{
	for (auto damage_ui : damage_uis_)
	{
		if (damage_ui->GetIsActive()) 
		{
			damage_ui->Update();
		}
	}
}

const void DamageUIGroup::Draw() const
{
	for (const auto damage_ui : damage_uis_)
	{
		if (damage_ui->GetIsActive())
		{
			damage_ui->Draw();
		}
	}
}

void DamageUIGroup::Spawn(const VECTOR& pos,const float& damage)
{
	for (auto damage_ui : damage_uis_)
	{
		if (!damage_ui->GetIsActive())
		{
			damage_ui->Spawn(pos, damage);
			break;
		}
	}
}

void DamageUIGroup::End()
{
	damage_uis_.clear();
}

DamageUIGroup::DamageUIGroup()
{

}