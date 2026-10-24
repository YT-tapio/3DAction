#include"DxLib.h"
#include"debug_camera.h"
#include"vector_assistant.h"
#include"FPS.h"
#include"input_base.h"
#include<unordered_map>
#include"input_manager.h"
#include"lerp.h"

DebugCamera::DebugCamera(VECTOR* pos,VECTOR* target_pos)
	: VirtualCameraBase(pos,target_pos)
	, future_pos_(VectorAssistant::VGetZero())
	, pitch_(0.f)
	, yaw_(80.f)
{
	input_ = InputManager::GetInstance().GetPlayer1Input();
}

DebugCamera::~DebugCamera()
{

}


void DebugCamera::Awake()
{

}

void DebugCamera::Init()
{

}

void DebugCamera::Update()
{
	// 自由に移動できるようにする
	ResetVel();
	VECTOR dir = VectorAssistant::VGetZero();
	
	auto main_camera_pos = *main_camera_pos_;
	auto main_camera_target_pos = *main_camera_target_pos_;
	dir = VectorAssistant::VGetDir(main_camera_pos, main_camera_target_pos);
	MoveTargetPos();
	MoveCamera(dir);
}

void DebugCamera::MoveTargetPos()
{
	target_to_camera_dist_size_ = VectorAssistant::VGetDistSize(*main_camera_target_pos_, *main_camera_pos_);

	// target_posを中心とし回転をさせる
	VECTOR input_value = VectorAssistant::VGetZero();
	VECTOR target_to_camera_dist = VectorAssistant::VGetZero();
	VECTOR next_pos = VectorAssistant::VGetZero();
	// playerの入力が必要
	// 入力値をもらう
	input_value = input_->GetCameraVelocity();

	float pitch_value = ((RadianAssistant::kOneRad * input_value.x) * 5.0f);
	float yaw_value = ((RadianAssistant::kOneRad * input_value.y) * 2.5f);
	
	pitch_ += (pitch_value * FPS::GetInstance().GetDeltaTime());
	yaw_ -= (yaw_value * FPS::GetInstance().GetDeltaTime());

	// yawの制限をする
	yaw_ = MyMath::Clampf(yaw_, RadianAssistant::kOneRad * kYawRadMin, RadianAssistant::kOneRad * kYawRadMax);

	// yawとpitchの位置を出してみる
	float pitch_size = 0.f;

	target_to_camera_dist.y = (cosf(yaw_) * target_to_camera_dist_size_);
	pitch_size = (sinf(yaw_) * target_to_camera_dist_size_);

	target_to_camera_dist.x = (cosf(pitch_) * pitch_size);
	target_to_camera_dist.z = (sinf(pitch_) * pitch_size);

	future_pos_ = VAdd(*main_camera_pos_, target_to_camera_dist);

	target_vel_ = VAdd(target_vel_, VSub(future_pos_, *main_camera_target_pos_));
}

void DebugCamera::MoveCamera(const VECTOR& dir)
{
	// カメラの移動(視点も移動する)

	VECTOR move_dir = VectorAssistant::VGetZero();

	if (CheckHitKey(KEY_INPUT_D))
	{
		auto offset_dir = VectorAssistant::VGetRotRadY(dir, 90);
		move_dir = offset_dir;
		move_dir.y = 0.f;
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		auto offset_dir = VectorAssistant::VGetRotRadY(dir, -90);
		move_dir = offset_dir;
		move_dir.y = 0.f;
	}

	if (CheckHitKey(KEY_INPUT_W))
	{ 
		move_dir = dir;
	}

	if (CheckHitKey(KEY_INPUT_S))
	{ 
		move_dir = VectorAssistant::VGetReverce(dir);
	}
	
	float speed = 0.1f;
	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		speed = 0.3f;
	}

	auto vel = VScale(move_dir, speed * FPS::GetInstance().GetDeltaTime()* FPS::GetInstance().GetTargetFPS());
	target_vel_ = VAdd(target_vel_, vel);
	vel_ = VAdd(vel_,vel);

}

void DebugCamera::ResetVel()
{
	vel_ = VectorAssistant::VGetZero();
	target_vel_ = VectorAssistant::VGetZero();
}