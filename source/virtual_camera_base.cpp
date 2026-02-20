#include"DxLib.h"
#include"virtual_camera_base.h"
#include"vector_assistant.h"

VirtualCameraBase::VirtualCameraBase()
{
	pos_		= VectorAssistant::VGetZero();
	target_pos_ = VectorAssistant::VGetZero();
	vel_		= VectorAssistant::VGetZero();
	target_vel_ = VectorAssistant::VGetZero();
}

VirtualCameraBase::~VirtualCameraBase()
{

}

void VirtualCameraBase::Init(const VECTOR& pos,const VECTOR& target_pos)
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