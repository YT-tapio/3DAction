#include<memory>
#include"just_one_node.h"
#include"behavior_status.h"

JustOneNode::JustOneNode()
	: NodeBase()
	, is_finished_(false)
{

}

JustOneNode::~JustOneNode()
{

}

void JustOneNode::Entry()
{
	
}

BehaviorStatus JustOneNode::Update()
{
	// ‚·‚Å‚ÉI‚í‚Á‚Ä‚¢‚é‚Ì‚È‚ç¸”s‚ğ•Ô‚·B
	if (is_finished_) { return BehaviorStatus::kFailure; }
	is_finished_ = true;
	return BehaviorStatus::kComplete;
}

void JustOneNode::Exit()
{

}