#include<map>
#include<memory>
#include"composite_node.h"
#include"sequence_node.h"
#include"node_status.h"

SequenceNode::SequenceNode(std::map<int, std::shared_ptr<NodeBase>, std::greater<int>> nodes)
	: CompositeNode(nodes)
{

}

SequenceNode::~SequenceNode()
{

}

NodeStatus SequenceNode::Update()
{
	return NodeStatus::kSuccess;
}