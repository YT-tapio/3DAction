#include<memory>
#include"DxLib.h"
#include"action_node.h"
#include"attack_node.h"
#include"behavior_status.h"

AttackNode::AttackNode()
	:ActionNode()
{

}

AttackNode::~AttackNode()
{

}

BehaviorStatus AttackNode::Update()
{
	static bool test = FALSE;
	if (test) { return BehaviorStatus::kSuccess; }
	printfDx("wow");
	test = TRUE;

	return BehaviorStatus::kSuccess;
}