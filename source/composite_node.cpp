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

void CompositeNode::Entry()
{
	// Å‰‚Ìnode‚Ìentry‚ðŒÄ‚Ô
	current_node_ = 0;
	nodes_[current_node_]->Entry();
}

BehaviorStatus CompositeNode::Update()
{
	return BehaviorStatus::kSuccess;
}

void CompositeNode::Exit()
{
	// ¡‚Ìnode‚Ìexit‚ðŒÄ‚Ô
	nodes_[current_node_]->Exit();
	current_node_ = 0;
}

void CompositeNode::Debug()
{
	for (auto& node : nodes_)
	{
		node->Debug();
	}
}