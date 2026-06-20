#include"node_base.h"
#include"behavior_status.h"

NodeBase::NodeBase()
	: status_(BehaviorStatus::kFailure)
{

}

NodeBase::~NodeBase()
{

}

void NodeBase::Init()
{

}

void NodeBase::Entry()
{

}

BehaviorStatus NodeBase::Update()
{
	return BehaviorStatus::kComplete;
}

void NodeBase::Exit()
{

}

void NodeBase::Debug()
{

}

const BehaviorStatus NodeBase::GetStatus() const
{
	return status_;
}