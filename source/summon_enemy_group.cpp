#include<memory>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"summon_enemy_group.h"
#include"behavior_status.h"
#include"enemy_summoner.h"

SummonEnemyGroup::SummonEnemyGroup(std::weak_ptr<ObjectBase> owner,std::shared_ptr<EnemySummoner> summoner,const VECTOR& pos,const std::string& enemy_group_name)
	: BehaviorBase(owner)
	, summoner_(summoner)
	, pos_(pos)
	, enemy_group_name_(enemy_group_name)
{

}

SummonEnemyGroup::~SummonEnemyGroup()
{

}

void SummonEnemyGroup::Entry()
{

}

BehaviorStatus SummonEnemyGroup::Update()
{
	// ¢Š«
	summoner_->Summon(enemy_group_name_, pos_);
	return BehaviorStatus::kComplete;
}

void SummonEnemyGroup::Exit()
{

}