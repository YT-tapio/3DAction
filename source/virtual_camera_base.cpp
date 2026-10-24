#include"DxLib.h"
#include"virtual_camera_base.h"
#include"vector_assistant.h"

VirtualCameraBase::VirtualCameraBase(VECTOR* pos,VECTOR* target_pos)
{
	main_camera_pos_ = pos;
	main_camera_target_pos_ = target_pos;
	vel_		= VectorAssistant::VGetZero();
	target_vel_ = VectorAssistant::VGetZero();
	is_active_ = FALSE;
	priority_ = 0;
	shake_power_ = 0.f;
}

VirtualCameraBase::~VirtualCameraBase()
{

}

void VirtualCameraBase::Init()
{
	
}

void VirtualCameraBase::Awake()
{

}

void VirtualCameraBase::Update()
{

}

void VirtualCameraBase::Active()
{
	is_active_ = TRUE;
}

void VirtualCameraBase::NotActive()
{
	is_active_ = FALSE;
}

VECTOR VirtualCameraBase::GetVelocity()
{
	return vel_;
}

VECTOR VirtualCameraBase::GetTargetVelocity()
{
	return target_vel_;
}

VECTOR VirtualCameraBase::GetPosFromYawPitch(const VECTOR& center_pos,const float& target_to_camera_dist_size, const float& yaw, const float& pitch)
{
	VECTOR target_to_camera_dist = VectorAssistant::VGetZero();
	VECTOR future_pos = VectorAssistant::VGetZero();

	// yawÇ∆pitchÇÃà íuÇèoÇµÇƒÇ›ÇÈ
	float pitch_size = 0.f;

	target_to_camera_dist.y = (cosf(yaw) * target_to_camera_dist_size);
	pitch_size = (sinf(yaw) * target_to_camera_dist_size);

	target_to_camera_dist.x = (cosf(pitch) * pitch_size);
	target_to_camera_dist.z = (sinf(pitch) * pitch_size);

	future_pos = VAdd(center_pos, target_to_camera_dist);

	return future_pos;
}