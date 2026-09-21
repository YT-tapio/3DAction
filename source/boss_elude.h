#pragma once
#include"boss_base.h"

class IShadowCreater;
class IEnemyUIGroup;
class IDamageUIGroup;
class IEnemyUIGroup;
class IAttackRangeGroup;
class NodeBase;
class EnemySummoner;

class BossElude : public BossBase
{
public:

	BossElude(const VECTOR& pos, bool* game_start, std::shared_ptr<IShadowCreater> shadow_creater,
		std::shared_ptr<IEnemyUIGroup> enemy_ui_group, std::shared_ptr<IDamageUIGroup> damage_ui_group,
		std::shared_ptr<IPlayerGroup> player_group, std::shared_ptr<IAttackRangeGroup> attack_range_group,std::shared_ptr<EnemySummoner> summoner);

	~BossElude() override;

	void Init() override;

	//void Update() override;

protected:

	virtual void MakeBehaviorTree(std::shared_ptr<EnemyBase> mine) override;

	void LoadFile() override;

private:

	std::shared_ptr<NodeBase> MakeMagicNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

	std::shared_ptr<NodeBase> MakeRoarTackleNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

	std::shared_ptr<NodeBase> MakeStampNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

	std::shared_ptr<NodeBase> MakeDoublePunchNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

	std::shared_ptr<NodeBase> MakeComboAttackNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

	std::shared_ptr<NodeBase> MakeChaseNode(std::shared_ptr<EnemyBase> mine);

	std::shared_ptr<NodeBase> MakeRoarNode(std::shared_ptr<EnemyBase> mine);

	std::shared_ptr<NodeBase> MakeSummonEnemyGroup(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

private:

	std::shared_ptr<EnemySummoner> summoner_;

};
