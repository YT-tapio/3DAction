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
#include"popup_ui_group_interface.h"
#include"player_group_interface.h"
#include"attack_range_group_interface.h"
#include"enemy_summoner.h"
#include"attack_type.h"
#include"status.h"
#include"status_container.h"
#include"attack_target_repository.h"
#include"enemy_movement_supporter.h"

EnemyGroup::EnemyGroup(bool* game_start, std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IEnemyUIGroup> enemy_ui_group,
	std::shared_ptr<IPopupUIGroup> damage_ui_group, std::shared_ptr<IPlayerGroup> player_group,
	std::shared_ptr<IAttackRangeGroup> attack_range_group,std::shared_ptr<EnemySummoner> summoner, 
	std::shared_ptr<AttackTargetRepository> attack_target_repository, std::shared_ptr<EnemyMovementSupporter> movement_supporter)
	: is_active_(FALSE)
{
	for (int i = 0; i < 3; i++)
	{
		auto pos = VGet(25, 0, 9 * (i + 1));
		auto minion = std::make_shared<MinionBase>(pos, game_start, shadow_creater, enemy_ui_group, damage_ui_group, player_group, attack_range_group, movement_supporter);
		attack_target_repository->AddTarget(Faction::enemy, minion.get());
		enemies_.emplace_back(minion);
		movement_supporter->AddResource(minion.get());
	}
	// ƒTƒ‚ƒi[‚É“o˜^
	summoner->Registration("name",this);
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

	// ‚à‚Æ‚Ìpos‚©‚çŒvŽZ‚µ‚Ä‚ðŠeX‚ð¶¬‚·‚é

	// 
	int i = 0;
	for (const auto& enemy : enemies_)
	{
		VECTOR offset_pos = VGet(i * 10.f, 0.f, 0.f);
		VECTOR summon_pos = VAdd(base_pos, offset_pos);
		enemy->Summon(summon_pos);
		i++;
	}

}

void EnemyGroup::BossDeath()
{
	//‚·‚×‚Ä‚ÌEnemy‚ÌHp‚ð0‚É

	for (auto enemy : enemies_)
	{
		auto hp = enemy->GetStatusContainer()->GetCurrentStatus().hp;
		if (hp > 0)
		{
			enemy->OnDamageFromPlayer(9999, AttackType::kPhysical, TRUE);
		}
	}

}

const bool EnemyGroup::GetIsActive() const
{
	return is_active_;
}


void EnemyGroup::LoadFile()
{

}