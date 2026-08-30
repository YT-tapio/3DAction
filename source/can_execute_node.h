#pragma once
#include"node_base.h"
#include"boss_enemy_attack_type.h"

class CanExecuteNode : public NodeBase
{
public:

	CanExecuteNode(std::function<bool(BossEnemyAttackType)> can_execute, BossEnemyAttackType type);

	~CanExecuteNode() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	// 
	std::function<bool(BossEnemyAttackType)> can_execute_;

	BossEnemyAttackType type_;

};

