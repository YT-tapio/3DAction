#include<vector>
#include<memory>
#include"composite_node.h"
#include"node_status.h"

CompositeNode::CompositeNode(std::vector<std::shared_ptr<NodeBase>> nodes)
	:nodes_(nodes)
	, current_node_(0)
{

}

CompositeNode::~CompositeNode()
{

}

NodeStatus CompositeNode::Update()
{
	return NodeStatus::kSuccess;
}