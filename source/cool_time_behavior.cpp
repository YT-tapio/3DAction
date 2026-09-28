#include<memory>
#include"cool_time_behavior.h"
#include"condition_timer.h"
#include"variable_timer.h"

CoolTimeBehavior::CoolTimeBehavior(const float& time)
	: IBehavior()
	, base_time_(time)
	, timer_(std::make_shared<VariableTimer>(time))
{

}

CoolTimeBehavior::~CoolTimeBehavior()
{

}

void CoolTimeBehavior::Init()
{

}

void CoolTimeBehavior::Entry()
{
	timer_->Stop();
	timer_->ChangeMaxTime(base_time_);
	timer_->ReStart();
}

BehaviorStatus CoolTimeBehavior::Update()
{
	timer_->Update();
	if (timer_->GetIsEnd())
	{
		return BehaviorStatus::kComplete;
	}
	return BehaviorStatus::kRunning;
}

void CoolTimeBehavior::Exit()
{
	timer_->Stop();
}

void CoolTimeBehavior::Draw()
{

}

void CoolTimeBehavior::Debug()
{

}