#include<vector>
#include<memory>
#include"composite_node.h"
#include"random_node.h"
#include"node_base.h"
#include"behavior_status.h"
#include"random.h"

RandomNode::RandomNode(std::vector<std::shared_ptr<NodeBase>> nodes)
	: CompositeNode(nodes)
{

}

RandomNode::~RandomNode()
{

}

void RandomNode::Entry()
{
	constexpr int kMin = 0;
	int max = nodes_.size();
	current_node_ = GetUniformRandom(kMin, max);
	nodes_[current_node_]->Entry();
	status_ = BehaviorStatus::kRunning;
}

BehaviorStatus RandomNode::Update()
{
	if (status_ == BehaviorStatus::kComplete)
	{
		nodes_[current_node_]->Exit();
		constexpr int kMin = 0;
		int max = nodes_.size();
		current_node_ = GetUniformRandom(kMin, max);
		nodes_[current_node_]->Entry();
	}
	status_ = nodes_[current_node_]->Update();
	return status_;
}

void RandomNode::Exit()
{
	nodes_[current_node_]->Exit();
}

void RandomNode::Debug()
{
	for (auto& node : nodes_)
	{
		node->Debug();
	}
}

