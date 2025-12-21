#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"camera.h"
#include"radian_assistant.h"
#include"vector_assistant.h"

Camera::Camera()
{
	const float kRad = 75.f;
	near_				= 0.1f;
	far_					= 1000.f;
	fov_					= RadianAssistant::TheNumRadian(kRad);
	pos_					= VGet(0.f, 0.f, 0.f);
	target_pos_		= VGet(0.f, 0.f, 10.f);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	Setting();
}

void Camera::Setting()
{
	SetCameraNearFar(near_, far_);
	SetupCamera_Perspective(fov_);
	SetCameraPositionAndTarget_UpVecY(pos_, target_pos_);
	Effekseer_Sync3DSetting();
	dir_ = VectorAssistant::VGetDir(pos_, target_pos_);
}