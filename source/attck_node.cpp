#include<memory>
#include"DxLib.h"
#include"action_node.h"
#include"attack_node.h"
#include"behavior_status.h"

AttackNode::AttackNode()
	:ActionNode(nullptr)
{

}

AttackNode::~AttackNode()
{

}

BehaviorStatus AttackNode::Update()
{
	return BehaviorStatus::kComplete;
}