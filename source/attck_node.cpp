#include<memory>
#include"DxLib.h"
#include"action_node.h"
#include"attack_node.h"
#include"node_status.h"

AttackNode::AttackNode()
	:ActionNode()
{

}

AttackNode::~AttackNode()
{

}

NodeStatus AttackNode::Update()
{
	static bool test = FALSE;
	if (test) { return NodeStatus::kSuccess; }
	printfDx("wow");
	test = TRUE;

	return NodeStatus::kSuccess;
}