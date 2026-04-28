#include<vector>
#include<memory>
#include"node_base.h"
#include"decorator_node.h"
#include"behavior_status.h"

DecoratorNode::DecoratorNode(std::unique_ptr<NodeBase> node)
	:NodeBase()
	,node_(std::move(node))
{

}

DecoratorNode::~DecoratorNode()
{

}

BehaviorStatus DecoratorNode::Update()
{
	// ğŒ‚ğ‚©‚­
	

	return BehaviorStatus::kFailure;
}