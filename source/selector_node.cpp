#include<map>
#include<memory>
#include"composite_node.h"
#include"selector_node.h"
#include"node_status.h"

SelectorNode::SelectorNode(std::map<int, std::shared_ptr<NodeBase>,std::greater<int>> nodes)
	:CompositeNode(nodes)
{

}

SelectorNode::~SelectorNode()
{

}

NodeStatus SelectorNode::Update()
{
	return NodeStatus::kSuccess;
}