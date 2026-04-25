#include<memory>
#include<functional>
#include<utility>
#include"node_base.h"
#include"branch_node.h"

BranchNode::BranchNode(std::pair<std::shared_ptr<NodeBase>,std::shared_ptr<NodeBase>> nodes,std::function<bool()> condition)
	: NodeBase()
	,nodes_(nodes)
	,condition_(condition)
{

}

BranchNode::~BranchNode()
{

}

void BranchNode::Update()
{
	if (condition_)
	{
		nodes_.first->Update();
	}
	else
	{
		nodes_.second->Update();
	}
}