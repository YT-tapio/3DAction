#pragma once
#include"status_holder_interface.h"
#include"enemy_base.h"

class IShadowCreater;
class NodeBase;

class BossBase : public EnemyBase
{
public:

	BossBase(const VECTOR& pos, bool* game_start,std::shared_ptr<IShadowCreater> shadow_creater);

	virtual ~BossBase() override;

	virtual void Init() override;

	virtual void Update() override;

protected:

	virtual void MakeBehaviorTree(std::shared_ptr<EnemyBase> mine);

	virtual void UpdatePhase();

	virtual void LoadFile() override;

private:

	std::shared_ptr<NodeBase> MakeMagicNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

	std::shared_ptr<NodeBase> MakeTackleNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

	std::shared_ptr<NodeBase> MakeStampNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

	std::shared_ptr<NodeBase> MakeDoublePunchNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase);

	std::shared_ptr<NodeBase> MakeChaseNode(std::shared_ptr<EnemyBase> mine);


};
