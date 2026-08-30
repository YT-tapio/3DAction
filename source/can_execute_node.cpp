#include<functional>
#include"can_execute_node.h"
#include"behavior_status.h"


CanExecuteNode::CanExecuteNode(std::function<bool(BossEnemyAttackType)> can_execute, BossEnemyAttackType type)
	: NodeBase()
	, can_execute_(can_execute)
	, type_(type)
{

}

CanExecuteNode::~CanExecuteNode()
{

}

void CanExecuteNode::Init()
{

}

void CanExecuteNode::Entry()
{

}

BehaviorStatus CanExecuteNode::Update()
{
	if (can_execute_ == nullptr) { return BehaviorStatus::kFailure; }

	if (can_execute_(type_))
	{
		return BehaviorStatus::kComplete;
	}

	return BehaviorStatus::kFailure;
}

void CanExecuteNode::Exit()
{

}