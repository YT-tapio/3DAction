#pragma once

class Time
{
public:

	Time();

	~Time();

	void Init();

	void Update();

	void SetTimeScale(const float& time_scale);

	void Debug();

	const float GetDeltaTime() const;

	const float GetFPSRate() const;

private:

	float base_delta_time_;
	float delta_time_;

	float time_scale_;


};