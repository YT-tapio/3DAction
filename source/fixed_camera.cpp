#include"DxLib.h"
#include"fixed_camera.h"
#include"lerp.h"
#include"condition_timer.h"
#include"variable_timer.h"

FixedCamera::FixedCamera(VECTOR* pos, VECTOR* target_pos, const VECTOR& my_pos, const VECTOR& my_target_pos,MoveTransitionMethod method,const float& speed)
	: VirtualCameraBase(pos,target_pos)
	, my_pos_(my_pos)
	, my_target_pos_(my_target_pos)
	, method_(method)
	, speed_(speed)
	, timer_(std::make_shared<VariableTimer>(speed))
{

}

FixedCamera::~FixedCamera()
{

}

void FixedCamera::Init()
{
	timer_->ReStart();
}

void FixedCamera::Update()
{
	// Ž©•ª‚ÌêŠ‚Ö‚Ì‘JˆÚ•û–@
	switch (method_)
	{
	case MoveTransitionMethod::kMoment:
		MomentUpdate();
		break;

	case MoveTransitionMethod::kLerp:
		LerpUpdate();
		break;

	case MoveTransitionMethod::kTimeLerp:
		TimeLerpUpdate();
		break;

	case MoveTransitionMethod::kDamp:
		DampUpdate();
		break;
	}
}

void FixedCamera::MomentUpdate()
{
	auto main_camera_pos = *main_camera_pos_;
	auto main_camera_target_pos = *main_camera_target_pos_;
	vel_ = VSub(my_pos_, main_camera_pos);
	target_vel_ = VSub(my_target_pos_, main_camera_target_pos);
}

void FixedCamera::LerpUpdate()
{
	auto main_camera_pos = *main_camera_pos_;
	auto main_camera_target_pos = *main_camera_target_pos_;
	vel_ = Lerp::LerpV(my_pos_, main_camera_pos, speed_);
	target_vel_ = Lerp::LerpV(my_target_pos_, main_camera_target_pos, speed_);
}

void FixedCamera::TimeLerpUpdate()
{
	timer_->Update();
	auto main_camera_pos = *main_camera_pos_;
	auto main_camera_target_pos = *main_camera_target_pos_;
	auto time_ratio = timer_->GetRatio();
	vel_ = VScale(VSub(my_pos_, main_camera_pos), time_ratio);
	target_vel_ = VScale(VSub(my_target_pos_, main_camera_target_pos), time_ratio);
}

void FixedCamera::DampUpdate()
{

}