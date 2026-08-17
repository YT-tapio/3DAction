#include<memory>
#include"action_node.h"
#include"behavior_tree.h"
#include"node_base.h"

BehaviorTree::BehaviorTree(std::shared_ptr<NodeBase> node)
	: node_(node)
	, is_first_(true)
{
	
}

BehaviorTree::~BehaviorTree()
{

}

void BehaviorTree::Init()
{
	is_first_ = true;
}

void BehaviorTree::Update()
{
	if (is_first_)
	{
		node_->Init();
		node_->Entry();
		is_first_ = false;
	}
	node_->Update();
}

void BehaviorTree::Debug()
{
	node_->Debug();
}
