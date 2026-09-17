#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include<functional>
#include"DxLib.h"
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
	: is_active_(FALSE)
{
	enemies_.emplace_back(std::make_shared<MinionBase>(VGet(20, 0, 5), game_start,shadow_creater, enemy_ui_group, damage_ui_group, player_group, attack_range_group));
	enemies_.emplace_back(std::make_shared<MinionBase>(VGet(20, 0, 15), game_start, shadow_creater, enemy_ui_group, damage_ui_group, player_group, attack_range_group));
	enemies_.emplace_back(std::make_shared<MinionBase>(VGet(20, 0, 25), game_start, shadow_creater, enemy_ui_group, damage_ui_group, player_group, attack_range_group));
	
	// ƒXƒ|ƒi[‚É“o˜^
	// summoner->Registration("name",this);
}

EnemyGroup::~EnemyGroup()
{

}

void EnemyGroup::Awake()
{
	is_active_ = FALSE;
	LoadFile();
}

void EnemyGroup::Init()
{
	is_active_ = FALSE;
	for (auto& enemy : enemies_)
	{
		enemy->Init();
	}
}

void EnemyGroup::Update()
{
	if (!is_active_) { return; }
	for (auto& enemy : enemies_)
	{
		enemy->Update();
	}
}

void EnemyGroup::Draw()
{
	if (!is_active_) { return; }
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

void EnemyGroup::Summon(const VECTOR& base_pos)
{
	is_active_ = TRUE;

	// ‚à‚Æ‚Ìpos‚©‚çŒvŽZ‚·‚é

}

const bool EnemyGroup::GetIsActive() const
{
	return is_active_;
}

void EnemyGroup::LoadFile()
{

}