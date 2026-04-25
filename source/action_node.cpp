#include<memory>
#include"action_node.h"

ActionNode::ActionNode()
	:NodeBase()
{

}

ActionNode::~ActionNode()
{

}

void ActionNode::Update()
{
	// アクションの実行
	action_->Update();
}