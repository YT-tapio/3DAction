#include<memory>
#include"DxLib.h"
#include"time.h"
#include"FPS.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"lerp.h"

Time::Time()
	: base_delta_time_(FPS::GetInstance().GetDeltaTime())
	, delta_time_(base_delta_time_)
	, target_time_scale_(1.f)
	, time_scale_(1.f)
	, change_scale_(FALSE)
{
	variable_timer_ = std::make_shared<VariableTimer>(0.f);
}

Time::~Time()
{

}

void Time::Init()
{
	base_delta_time_ = FPS::GetInstance().GetDeltaTime();
	target_time_scale_ = 1.f;
	time_scale_ = 1.f;
	delta_time_ = base_delta_time_ * time_scale_;
}

void Time::Update()
{

	if (change_scale_)
	{
		// 変化方法
		switch (transition_method_)
		{
		case TimeTransitionMethod::kLerp:
			time_scale_ = Lerp::Lerpf(time_scale_, target_time_scale_, 1.f);
			break;

		case TimeTransitionMethod::kDamp:
			time_scale_ = Lerp::Dampf(time_scale_, target_time_scale_, 0.4f);
			break;
		}

		if (time_scale_ == target_time_scale_)
		{
			// タイマーを動かす
			variable_timer_->Update();
			// variable_timer_->
			if(variable_timer_->GetIsEnd())
			{
				target_time_scale_ = 1.f;
				if (transition_method_ == TimeTransitionMethod::kMoment) { time_scale_ = target_time_scale_; }
			}

			// baseに戻ったら
			if (time_scale_ == 1.f)
			{
				change_scale_ = FALSE;
			}
		}

		printfDx("time_scale:%.2f\n", time_scale_);
		printfDx("target_time_scale:%.2f\n", target_time_scale_);

	}

	base_delta_time_ = FPS::GetInstance().GetDeltaTime();
	delta_time_ = base_delta_time_ * time_scale_;
}

void Time::SetTimeScale(const float& target_time_scale, const float& time,TimeTransitionMethod method)
{
	target_time_scale_ = target_time_scale;
	transition_method_ = method;
	if (transition_method_ == TimeTransitionMethod::kMoment) { time_scale_ = target_time_scale_; }
	variable_timer_->Stop();
	variable_timer_->ChangeMaxTime(time);
	variable_timer_->ReStart();
	change_scale_ = TRUE;
}

const float Time::GetDeltaTime() const
{
	return delta_time_;
}

const float Time::GetFPSRate() const
{
	return delta_time_ * FPS::GetInstance().GetTargetFPS();
}
