#include"node_base.h"
#include"node_status.h"

NodeBase::NodeBase()
{

}

NodeBase::~NodeBase()
{

}

NodeStatus NodeBase::Update()
{
	return NodeStatus::kSuccess;
}