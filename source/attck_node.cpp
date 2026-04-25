#include<memory>
#include"DxLib.h"
#include"action_node.h"
#include"attack_node.h"


AttackNode::AttackNode()
	:ActionNode()
{

}

AttackNode::~AttackNode()
{

}

void AttackNode::Update()
{
	static bool test = FALSE;
	if (test) { return; }
	printfDx("wow");
	test = TRUE;
}