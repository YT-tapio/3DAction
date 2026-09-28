#include"check_enemy_attack_id.h"
#include"attack_id.h"

CheckEnemyAttackID::CheckEnemyAttackID(AttackID* current_attack_id, AttackID target_attack_id)
	: IBehavior()
	, current_attack_id_(current_attack_id)
	, target_attack_id_(target_attack_id)
{

}

CheckEnemyAttackID::~CheckEnemyAttackID()
{

}

void CheckEnemyAttackID::Init()
{

}

void CheckEnemyAttackID::Entry()
{

}

BehaviorStatus CheckEnemyAttackID::Update()
{
	return target_attack_id_ == *current_attack_id_ ? BehaviorStatus::kComplete : BehaviorStatus::kFailure;
}

void CheckEnemyAttackID::Exit()
{

}