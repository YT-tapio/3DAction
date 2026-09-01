#include"check_count_node.h"
#include"behavior_status.h"


CheckCountNode::CheckCountNode(const int& target_count)
	: NodeBase()
	, current_count_(0)
	, target_count_(target_count)
{

}

CheckCountNode::~CheckCountNode()
{

}


void CheckCountNode::Init()
{
	current_count_ = 0;
}

void CheckCountNode::Entry()
{
	
}

BehaviorStatus CheckCountNode::Update()
{
	if(target_count_ == current_count_)
	{
		current_count_ = 0;
		return BehaviorStatus::kFailure;
	}
	current_count_++;
	return BehaviorStatus::kComplete;
}

void CheckCountNode::Exit()
{
	
}