#include<vector>
#include<memory>
#include"composite_node.h"
#include"behavior_status.h"

CompositeNode::CompositeNode(std::vector<std::shared_ptr<NodeBase>> nodes)
	:nodes_(nodes)
	, current_node_(0)
{

}

CompositeNode::~CompositeNode()
{

}

void CompositeNode::Init()
{
	for (auto& node : nodes_)
	{
		node->Init();
	}
}

BehaviorStatus CompositeNode::Update()
{
	return BehaviorStatus::kSuccess;
}

void CompositeNode::Debug()
{
	for (auto& node : nodes_)
	{
		node->Debug();
	}
}