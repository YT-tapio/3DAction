#pragma once
#define DEF_FPSCONTROLL_H

class FPS
{
public:

	static FPS& GetInstance()
	{
		static FPS fps;
		return fps;
	}

	FPS(const FPS&) = delete;
	FPS& operator = (const FPS&) = delete;

	void Init();


	void Update();


	void Wait();


	void SetTimeScale(float time_scale)
	{
		time_scale_ = time_scale;
	}


	const float GetDeltaTime() const { return delta_time_; }

	void Debug();
	
private:

	// É}ÉCÉNÉçïbêî
	static constexpr float kUS = 0.000001f;

	static constexpr float  kTargetFps = 60.0f;
	static constexpr float kTargetFrameTime = 1.f / kTargetFps;

	LONGLONG prev_time_;
	LONGLONG now_time_;
	LONGLONG first_time_;
	float took_time_ = 0.f;
	float sleep_time_ = 0.f;
	float wait_time_ = 0.f;
	float delta_time_;
	float now_fps_;
	float time_scale_;

	int count_;

	FPS();

	void DrawDeltaTime();

	void DrawTimeScale();


};