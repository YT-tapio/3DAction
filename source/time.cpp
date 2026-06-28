#include"DxLib.h"
#include"time.h"
#include"FPS.h"

Time::Time()
	: base_delta_time_(FPS::GetInstance().GetDeltaTime())
	, delta_time_(base_delta_time_)
	, time_scale_(1.f)
{

}

Time::~Time()
{

}

void Time::Init()
{
	base_delta_time_ = FPS::GetInstance().GetDeltaTime();
	time_scale_ = 1.f;
	delta_time_ = base_delta_time_ * time_scale_;
}

void Time::Update()
{
	base_delta_time_ = FPS::GetInstance().GetDeltaTime();
	delta_time_ = base_delta_time_ * time_scale_;
}

void Time::SetTimeScale(const float& time_scale)
{
	time_scale_ = time_scale;
}

const float Time::GetDeltaTime() const
{
	return delta_time_;
}

const float Time::GetFPSRate() const
{
	return delta_time_ * FPS::GetInstance().GetTargetFPS();
}
