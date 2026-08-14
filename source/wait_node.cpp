#include<memory>
#include"wait_node.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"behavior_status.h"
#include"random.h"

WaitNode::WaitNode(std::shared_ptr<NodeBase> node,const float& min,const float& max)
	: node_(node)
	, timer_(std::make_shared<VariableTimer>())
	, min_(min)
	, max_(max)
{
	
}

WaitNode::~WaitNode()
{

}

void WaitNode::Init()
{
	timer_->Init();
}

void WaitNode::Entry()
{
	// タイマーの起動
	auto random_wait_time = GetUniformRandom(min_, max_);
	timer_->Stop();
	timer_->ChangeMaxTime(random_wait_time);
	timer_->ReStart();
}

BehaviorStatus WaitNode::Update()
{
	// タイマーの更新
	timer_->Update();

	//タイマーが終了したとき終了
	if (timer_->GetIsEnd())
	{
		return BehaviorStatus::kComplete;
	}
	return BehaviorStatus::kRunning;
}

void WaitNode::Exit()
{

}

void WaitNode::Debug()
{

}