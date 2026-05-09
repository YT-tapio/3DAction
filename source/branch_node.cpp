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
	, status_(BehaviorStatus::kFailure)
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

BehaviorStatus BranchNode::Update()
{
	if (status_ != BehaviorStatus::kRunning)
	{
		is_first_update_ = condition_();
	}
	
	if(is_first_update_)
	{
		status_ = nodes_.first->Update();
	}
	else
	{
		status_ = nodes_.second->Update();
	}

	/*
	status_ = is_first_update_ ? nodes_.first->Update() : nodes_.second->Update();
	*/
	

	if (status_ == BehaviorStatus::kSuccess)
	{
		if (is_first_update_)
		{
			nodes_.first->Exit();
		}
		else
		{
			nodes_.second->Exit();
		}

		/*
		is_first_update_ ? nodes_.first->Exit() : nodes_.second->Exit();
		*/
		
	}

	return status_;
}

void BranchNode::Debug()
{
	nodes_.first->Debug();
	nodes_.second->Debug();
}