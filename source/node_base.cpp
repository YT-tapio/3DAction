#include"node_base.h"
#include"behavior_status.h"

NodeBase::NodeBase()
{

}

NodeBase::~NodeBase()
{

}

BehaviorStatus NodeBase::Update()
{
	return BehaviorStatus::kSuccess;
}