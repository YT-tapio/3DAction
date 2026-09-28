#pragma once
#include"behavior_interface.h"
enum class AttackID;

class CheckEnemyAttackID : public IBehavior
{
public:

	CheckEnemyAttackID(AttackID* attack_id, AttackID target_attack_id);

	~CheckEnemyAttackID() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	AttackID* current_attack_id_;
	AttackID target_attack_id_;
};
