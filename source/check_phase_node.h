#pragma once
#include"node_base.h"
#include"phase.h"

class CheckPhaseNode : public NodeBase
{
public:

	CheckPhaseNode(const Phase my_phase,std::function<Phase()> current_phase);

	~CheckPhaseNode() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	Phase my_phase_;

	std::function<Phase()> current_phase_;

};