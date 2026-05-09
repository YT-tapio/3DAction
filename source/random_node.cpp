#include<vector>
#include<memory>
#include"composite_node.h"
#include"random_node.h"
#include"node_base.h"
#include"behavior_status.h"
#include"random.h"

RandomNode::RandomNode(std::vector<std::shared_ptr<NodeBase>> nodes)
	: CompositeNode(nodes)
	, status_(BehaviorStatus::kFailure)
{

}

RandomNode::~RandomNode()
{

}

void RandomNode::Init()
{

}

void RandomNode::Entry()
{

}

BehaviorStatus RandomNode::Update()
{
	if (status_ == BehaviorStatus::kSuccess)
	{
		nodes_[current_node_]->Entry();
		constexpr int kMin = 0;
		int max = nodes_.size();
		current_node_ = GetRandom(kMin, max);
		nodes_[current_node_]->Exit();
	}

	return nodes_[current_node_]->Update();
}

void RandomNode::Exit()
{
	nodes_[current_node_]->Exit();
}

void RandomNode::Debug()
{

}

