#include"DxLib.h"
#include"virtual_camera_base.h"
#include"vector_assistant.h"

VirtualCameraBase::VirtualCameraBase()
{
	pos_		= VectorAssistant::VGetZero();
	target_pos_ = VectorAssistant::VGetZero();
}

VirtualCameraBase::~VirtualCameraBase()
{

}

void VirtualCameraBase::Init(const VECTOR& pos,const VECTOR& target_pos)
{

}

VECTOR VirtualCameraBase::Update()
{
	



	return VectorAssistant::VGetZero();
}