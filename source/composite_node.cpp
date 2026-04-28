#include<map>
#include<memory>
#include"composite_node.h"
#include"node_status.h"
CompositeNode::CompositeNode(std::map<int, std::shared_ptr<NodeBase>,std::greater<int>> nodes)
	:nodes_(nodes)
{

}

CompositeNode::~CompositeNode()
{

}

NodeStatus CompositeNode::Update()
{
	return NodeStatus::kSuccess;
}