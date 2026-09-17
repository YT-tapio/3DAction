#pragma once
#include"behavior_base.h"

class ObjectBase;
class EnemySummoner;

class SummonEnemyGroup : public BehaviorBase
{
public:

	SummonEnemyGroup(std::weak_ptr<ObjectBase> owner, std::shared_ptr<EnemySummoner> summoner, const VECTOR& pos, const std::string& name);

	~SummonEnemyGroup() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	std::shared_ptr<EnemySummoner> summoner_;

	VECTOR pos_;

	std::string enemy_group_name_;

};
