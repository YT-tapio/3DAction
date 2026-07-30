#include<memory>
#include"wait_node.h"
#include"condition_timer.h"
#include"behavior_status.h"

WaitNode::WaitNode(std::shared_ptr<NodeBase> node,const float time)
	: node_(node)
	, timer_(std::make_shared<ConditionTimer>(time))
{

}

WaitNode::~WaitNode()
{

}

void WaitNode::Init()
{
	timer_->Init();
}

void WaitNode::Entry()
{
	// タイマーの起動

}

BehaviorStatus WaitNode::Update()
{

	return BehaviorStatus::kComplete;
}

void WaitNode::Exit()
{

}

void WaitNode::Debug()
{

}