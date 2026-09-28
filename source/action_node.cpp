#include<memory>
#include"action_node.h"
#include"behavior_status.h"
#include"behavior_interface.h"

ActionNode::ActionNode(std::shared_ptr<IBehavior> action)
	: NodeBase()
	, action_(action)
{

}

ActionNode::~ActionNode()
{

}

void ActionNode::Init()
{
	action_->Init();
}

void ActionNode::Entry()
{
	action_->Entry();
}

BehaviorStatus ActionNode::Update()
{
	// アクションの実行
	status_ = action_->Update();
	return status_;
}

void ActionNode::Exit()
{
	action_->Exit();
}

void ActionNode::Debug()
{
	action_->Debug();
}