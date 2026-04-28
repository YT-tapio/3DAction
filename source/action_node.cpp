#include<memory>
#include"action_node.h"
#include"behavior_status.h"

ActionNode::ActionNode()
	:NodeBase()
{

}

ActionNode::~ActionNode()
{

}

BehaviorStatus ActionNode::Update()
{
	// アクションの実行
	action_->Update();
	return BehaviorStatus::kSuccess;
}