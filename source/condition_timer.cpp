#include<math.h>
#include"DxLib.h"
#include"condition_timer.h"
#include"FPS.h"


ConditionTimer::ConditionTimer(float max_time)
	: is_stop_(FALSE)
	, is_end_(FALSE)
	, max_time_(max_time)
	, time_(0.f)

{

}

ConditionTimer::~ConditionTimer()
{

}

void ConditionTimer::Init()
{
	time_ = 0.f;
	is_stop_ = FALSE;
	is_end_ = FALSE;
}

void ConditionTimer::Update()
{
	if (is_stop_)	{ return; }
	if (is_end_)	{ return; }
	time_ += FPS::GetInstance().GetDeltaTime();
	if (time_ > max_time_) { time_ = max_time_; is_end_ = TRUE; }
}

void ConditionTimer::Stop()
{
	is_stop_ = FALSE;
}

void ConditionTimer::Start()
{
	is_stop_ = FALSE;
	is_end_ = FALSE;
	time_ = 0.f;
}

void ConditionTimer::ReStart()
{
	is_stop_ = FALSE;
	is_end_ = FALSE;
}

const bool ConditionTimer::GetIsStop() const
{
	return is_stop_;
}

const bool ConditionTimer::GetIsEnd() const
{
	return is_end_;
}
