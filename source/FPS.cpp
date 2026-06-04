#include<math.h>
#include"DxLib.h"
#include"FPS.h"


FPS::FPS()
	: prev_time_(GetNowHiPerformanceCount())
	, first_time_(GetNowHiPerformanceCount())
	, now_time_(0.0f)
	, delta_time_(0.0f)
	, count_(0)
	, now_fps_(0.0f)
	, time_scale_(1.0f)
{

}



void FPS::Init()
{
	first_time_ = GetNowHiPerformanceCount();
	prev_time_ = GetNowHiPerformanceCount();
	now_time_ = 0.0f;
	delta_time_ = 0.0f;
	count_ = 1;
	now_fps_ = 0.0f;
}


void FPS::Update()
{
	now_time_ = GetNowHiPerformanceCount();
	delta_time_ = (now_time_ - prev_time_) * kUS;
	prev_time_ = now_time_;

	if (count_ == kTargetFps)
	{
		// 経過時間
		const auto elapsed_time = (now_time_ - first_time_);
		now_fps_ = kTargetFps  / (elapsed_time * kUS);
		// 最初の瞬間を記憶
		first_time_ = GetNowHiPerformanceCount();
		count_ = 1;
	}
	else
	{
		count_++;
	}

	
}

void FPS::Wait()
{
	// 実際にかかった時間(秒)kUSをかけてsにする
	float took_time = (GetNowHiPerformanceCount() - now_time_) * kUS;
	// 1フレーム何m秒かかるかと実際にかかった時間をくらべる
	float wait_time_ms = (kTargetFrameTime - took_time) * 1000.f;
	
	auto before = GetNowHiPerformanceCount();

	// かかった時間が以上なら
	if (wait_time_ms > 0.f)
	{
		Sleep(static_cast<DWORD>(wait_time_ms));
	}

	auto after = GetNowHiPerformanceCount();
	//スリープにかかった時間
	if (count_ == 1)
	{
		took_time_ = took_time * 1000.f;
		wait_time_ = wait_time_ms;
		sleep_time_ = (after - before) * kUS * 1000.f;
	}
	


}

void FPS::Debug()
{
	DrawFormatString(300, 100, GetColor(255, 255, 255), "%d", count_);
	DrawDeltaTime();
}


void FPS::DrawDeltaTime()
{
	DrawFormatString(400, 80, GetColor(255, 255, 255), "%.2f", now_fps_);
	DrawFormatString(400, 100, GetColor(255, 255, 255), "%f", delta_time_);
	DrawFormatString(400, 120, GetColor(255, 255, 255), "took_time:%f", took_time_);
	DrawFormatString(400, 140, GetColor(255, 255, 255), "wait_time:%f", wait_time_);
	DrawFormatString(400, 160, GetColor(255, 255, 255), "sleep_time:%f", sleep_time_);
	DrawFormatString(400, 180, GetColor(255, 255, 255), "%f", wait_time_ - sleep_time_);
}


void FPS::DrawTimeScale()
{
	DrawFormatString(500, 100, GetColor(255, 255, 255), "%f", time_scale_);
}