#include"DxLib.h"
#include"virtual_camera_base.h"
#include"vector_assistant.h"

VirtualCameraBase::VirtualCameraBase(VECTOR* pos,VECTOR* target_pos)
{
	pos_ = pos;
	target_pos_ = target_pos;
	vel_		= VectorAssistant::VGetZero();
	target_vel_ = VectorAssistant::VGetZero();
	is_active_ = FALSE;
	priority_ = 0;
}

VirtualCameraBase::~VirtualCameraBase()
{

}

void VirtualCameraBase::Init()
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