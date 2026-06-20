#include<memory>
#include<functional>
#include<utility>
#include"node_base.h"
#include"branch_node.h"
#include"behavior_status.h"

BranchNode::BranchNode(std::pair<std::shared_ptr<NodeBase>,std::shared_ptr<NodeBase>> nodes,std::function<bool()> condition)
	: NodeBase()
	, nodes_(nodes)
	, condition_(condition)
	, is_first_update_(false)
{
	
}

BranchNode::~BranchNode()
{

}

void BranchNode::Init()
{
	nodes_.first->Init();
	nodes_.second->Init();
}

void BranchNode::Entry()
{
	is_first_update_ = condition_();
	is_first_update_ ? nodes_.first->Entry() : nodes_.second->Entry();
}

BehaviorStatus BranchNode::Update()
{
	if (status_ == BehaviorStatus::kComplete)
	{
		is_first_update_ ? nodes_.first->Exit() : nodes_.second->Exit();
		is_first_update_ = condition_();
		is_first_update_ ? nodes_.first->Entry() : nodes_.second->Entry();
	}
	
	status_ = is_first_update_ ? nodes_.first->Update() : nodes_.second->Update();

	return status_;
}

void BranchNode::Exit()
{
	
}

void BranchNode::Debug()
{
	nodes_.first->Debug();
	nodes_.second->Debug();
}