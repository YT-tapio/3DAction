#pragma once
#include"time_transition_method.h"

class VariableTimer;

class Time
{
public:

	Time();

	~Time();

	void Init();

	void Update();

	void SetTimeScale(const float& time_scale, const float& time,TimeTransitionMethod method = TimeTransitionMethod::kMoment);

	void Debug();

	const float GetDeltaTime() const;

	const float GetFPSRate() const;

private:

	TimeTransitionMethod transition_method_;
	std::shared_ptr<VariableTimer> variable_timer_;

	// デルタタイム
	float base_delta_time_;
	float delta_time_;

	float target_time_scale_;
	float time_scale_;

	bool change_scale_;

};