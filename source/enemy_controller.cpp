#include<memory>
#include<functional>
#include<vector>
#include<string>
#include"DxLib.h"
#include"enemy_controller.h"
#include"enemy_base.h"
#include"boss_base.h"
#include"boss_elude.h"
#include"enemy_group.h"
#include"vector_assistant.h"
#include"enemy_observer_interface.h"
#include"enemy_summoner.h"

EnemyController::EnemyController(bool* game_start, std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IEnemyUIGroup> enemy_ui_group, std::shared_ptr<IDamageUIGroup> damage_ui_group,
	std::shared_ptr<IPlayerGroup> player_group, std::shared_ptr<IAttackRangeGroup> attack_range_group)
{
	summoner_ = std::make_shared<EnemySummoner>();
	boss_ = std::make_shared<BossElude>(VectorAssistant::VGetZero(), game_start, shadow_creater, enemy_ui_group, damage_ui_group, player_group, attack_range_group, summoner_);
	enemy_groups_.push_back(std::make_shared<EnemyGroup>(game_start, shadow_creater, enemy_ui_group, damage_ui_group, player_group, attack_range_group,summoner_));
}

EnemyController::~EnemyController()
{

}

void EnemyController::Awake()
{
	
	for (auto& enemy_group : enemy_groups_)
	{
		enemy_group->Awake();
	}
}

void EnemyController::Init()
{
	boss_->Init();
	
	for (auto& enemy_group : enemy_groups_)
	{
		enemy_group->Init();
	}
	
}

void EnemyController::Update()
{
	boss_->Update();
	
	for (auto& enemy_group : enemy_groups_)
	{
		enemy_group->Update();
	}
}

void EnemyController::AddBossObserver(IEnemyObserver* observer)
{
	boss_->AddObserver(observer);
}

const void EnemyController::Draw() const
{
	boss_->Draw();
	
	for (const auto& enemy_group : enemy_groups_)
	{
		enemy_group->Draw();
	}
	
	
}

const VECTOR EnemyController::GetBossCenterPos() const
{
	return boss_->GetCenterPos();
}

const VECTOR EnemyController::GetBossFrontDir() const
{
	return boss_->GetFrontDir();
}