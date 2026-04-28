#include<memory>
#include"action_node.h"
#include"node_status.h"

ActionNode::ActionNode()
	:NodeBase()
{

}

ActionNode::~ActionNode()
{

}

NodeStatus ActionNode::Update()
{
	// アクションの実行
	action_->Update();
	return NodeStatus::kSuccess;
}