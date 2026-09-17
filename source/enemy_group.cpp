#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include<functional>
#include"enemy_group.h"
#include"enemy_base.h"
#include"minion_base.h"

#include"shadow_creater_interface.h"
#include"enemy_ui_group_interface.h"
#include"damage_ui_group_interface.h"
#include"player_group_interface.h"
#include"attack_range_group_interface.h"

EnemyGroup::EnemyGroup(bool* game_start, std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IEnemyUIGroup> enemy_ui_group,
	std::shared_ptr<IDamageUIGroup> damage_ui_group, std::shared_ptr<IPlayerGroup> player_group, std::shared_ptr<IAttackRangeGroup> attack_range_group)
{
	enemies_.emplace_back(std::make_shared<MinionBase>(VGet(20, 0, 5), game_start,shadow_creater, enemy_ui_group, damage_ui_group, player_group, attack_range_group));
	enemies_.emplace_back(std::make_shared<MinionBase>(VGet(20, 0, 15), game_start, shadow_creater, enemy_ui_group, damage_ui_group, player_group, attack_range_group));
	enemies_.emplace_back(std::make_shared<MinionBase>(VGet(20, 0, 25), game_start, shadow_creater, enemy_ui_group, damage_ui_group, player_group, attack_range_group));
}

EnemyGroup::~EnemyGroup()
{

}

void EnemyGroup::Awake()
{
	LoadFile();
}

void EnemyGroup::Init()
{
	for (auto& enemy : enemies_)
	{
		enemy->Init();
	}
}

void EnemyGroup::Update()
{
	for (auto& enemy : enemies_)
	{
		enemy->Update();
	}
}

void EnemyGroup::Draw()
{
	for (const auto& enemy : enemies_)
	{
		enemy->Draw();
	}
}

void EnemyGroup::Debug()
{
	for (const auto& enemy : enemies_)
	{
		enemy->Debug();
	}
}

void EnemyGroup::LoadFile()
{

}