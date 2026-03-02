#include<memory>
#include"DxLib.h"
#include"sphere_camera.h"
#include"input_base.h"
#include"input_manager.h"
#include"radian_assistant.h"
#include"vector_assistant.h"
#include"FPS.h"

SphereCamera::SphereCamera(VECTOR* center_pos,VECTOR* pos, VECTOR* target_pos)
	:VirtualCameraBase(pos,target_pos)
{
	center_pos_ = center_pos;
	rotation_ = VectorAssistant::VGetZero();
	input_ = InputManager::GetInstance().GetPlayerInput();
	target_to_camera_dist_size_ = 0.f;
}

SphereCamera::~SphereCamera()
{

}

void SphereCamera::Init()
{
	
	VECTOR target_to_camera_dist		= VSub(*pos_, *target_pos_);
	VECTOR target_pos_to_camera_dir		= VNorm(target_to_camera_dist);
	// 真上
	VECTOR a = VGet(0.f, 1.f, 0.f);

	// 角度を出す
	yaw_ = VectorAssistant::GetTwoVectorRad(a, target_pos_to_camera_dir);
	pitch_ = atan2f(target_pos_to_camera_dir.z, target_pos_to_camera_dir.x);
	target_to_camera_dist_size_ = VSize(target_to_camera_dist);

	target_vel_ = VSub(*center_pos_, *target_pos_);
}

void SphereCamera::Update()
{
	vel_ = VectorAssistant::VGetZero();
	target_vel_ = VectorAssistant::VGetZero();
	// target_posを中心とし回転をさせる
	VECTOR input_value = VectorAssistant::VGetZero();
	VECTOR target_to_camera_dist = VectorAssistant::VGetZero();
	VECTOR next_pos = VectorAssistant::VGetZero();
	// playerの入力が必要
	// 入力値をもらう
	input_value = input_->GetCameraVelocity();

	float pitch_value	= ((RadianAssistant::kOneRad * input_value.x) * 5.0f);
	float yaw_value		= ((RadianAssistant::kOneRad * input_value.y) * 2.5f);

	pitch_	+= (pitch_value * FPS::GetInstance().GetDeltaTime());
	yaw_	+= (yaw_value * FPS::GetInstance().GetDeltaTime());
	
	//yawの制限をする
	// yawとpitchの位置を出してみる
	float pitch_size = 0.f;
	
	target_to_camera_dist.y = (cosf(yaw_) * target_to_camera_dist_size_);
	pitch_size				= (sinf(yaw_) * target_to_camera_dist_size_);

	target_to_camera_dist.x = (cosf(pitch_) * pitch_size);
	target_to_camera_dist.z = (sinf(pitch_) * pitch_size);

	next_pos = VAdd(*target_pos_, target_to_camera_dist);

	vel_ = VAdd(vel_, VSub(next_pos, *pos_));
	if (!VectorAssistant::IsSamePos(*center_pos_, *target_pos_))
	{
		target_vel_ = VSub(*center_pos_, *target_pos_);
	}
	else
	{
		target_vel_ = VectorAssistant::VGetZero();
	}
	
}

