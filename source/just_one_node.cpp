#include<memory>
#include"just_one_node.h"
#include"behavior_status.h"

JustOneNode::JustOneNode(std::shared_ptr<BehaviorBase> action)
	: ActionNode(action)
	, is_finished_(false)
{

}

JustOneNode::~JustOneNode()
{

}

void JustOneNode::Entry()
{
	if (is_finished_) { return; }
	ActionNode::Entry();
}

BehaviorStatus JustOneNode::Update()
{
	// ‚·‚Å‚ÉI‚í‚Á‚Ä‚¢‚é‚Ì‚È‚ç¸”s‚ğ•Ô‚·B
	if (is_finished_) { return BehaviorStatus::kFailure; }
	auto status = ActionNode::Update();
	if (status == BehaviorStatus::kComplete)
	{
		is_finished_ = true;
	}

	return status;
}