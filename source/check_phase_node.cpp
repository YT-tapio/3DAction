#include<functional>
#include"check_phase_node.h"
#include"behavior_status.h"

CheckPhaseNode::CheckPhaseNode(const Phase phase,std::function<Phase()> current_phase)
	: NodeBase()
	, my_phase_(phase)
	, current_phase_(current_phase)
{

}

CheckPhaseNode::~CheckPhaseNode()
{

}

void CheckPhaseNode::Init()
{

}

void CheckPhaseNode::Entry()
{

}

BehaviorStatus CheckPhaseNode::Update()
{
	// 敵のフェーズ
	if (current_phase_() >= my_phase_)
	{
		return BehaviorStatus::kComplete;
	}

	return BehaviorStatus::kFailure;
}

void CheckPhaseNode::Exit()
{

}