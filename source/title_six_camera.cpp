#include"DxLib.h"
#include"title_six_camera.h"
#include"vector_assistant.h"

#include"condition_timer.h"
#include"variable_timer.h"

TitleSixCamera::TitleSixCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos)
	: VirtualCameraBase(main_camera_pos,main_camera_target_pos)
	, timer_(std::make_shared<ConditionTimer>(1.f))
	, phase_(Phase::kFirst)
{

}

TitleSixCamera::~TitleSixCamera()
{

}

void TitleSixCamera::Awake()
{
	timer_->Init();
}

void TitleSixCamera::Init()
{
	phase_ = Phase::kFirst;
	timer_->Init();
	timer_->ReStart();
}

void TitleSixCamera::Update()
{
	

	switch (phase_)
	{
	case Phase::kFirst:
		FirstPhaseUpdate();
		break;

	case Phase::kSecond:
		SecondPhaseUpdate();
		break;
	}
	auto main_camera_target_pos = *main_camera_target_pos_;
	target_vel_ = VSub(kInitTargetPos, main_camera_target_pos);
}

void TitleSixCamera::FirstPhaseUpdate()
{
	auto main_camera_pos = *main_camera_pos_;
	vel_ = VSub(kInitPos, main_camera_pos);
	phase_ = Phase::kSecond;
}

void TitleSixCamera::SecondPhaseUpdate()
{
	timer_->Update();
	auto main_camera_pos = *main_camera_pos_;
	auto dist = VSub(kLastPos, main_camera_pos);
	vel_ = VScale(dist, timer_->GetRatio());
}