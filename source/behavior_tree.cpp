#include<memory>
#include"action_node.h"
#include"behavior_tree.h"
#include"node_base.h"
#include"attack_node.h"

BehaviorTree::BehaviorTree()
{
	
}

BehaviorTree::~BehaviorTree()
{

}

void BehaviorTree::Update()
{
	node_->Update();
}
