#include<memory>
#include"action_node.h"
#include"behavior_status.h"

ActionNode::ActionNode(std::shared_ptr<BehaviorBase> action)
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

BehaviorStatus ActionNode::Update()
{
	// アクションの実行
	return action_->Update();
}


void ActionNode::Debug()
{
	action_->Debug();
}