#include<memory>
#include"action_node.h"
#include"behavior_tree.h"
#include"node_base.h"
#include"attack_node.h"

BehaviorTree::BehaviorTree(std::shared_ptr<NodeBase> node)
	: node_(node)
{
	
}

BehaviorTree::~BehaviorTree()
{

}

void BehaviorTree::Init()
{
	//node_->Init();
}

void BehaviorTree::Update()
{
	node_->Update();
}
