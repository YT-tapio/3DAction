#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"camera.h"
#include"radian_assistant.h"
#include"vector_assistant.h"
#include"color.h"
#include"debug.h"
#include"brain.h"

Camera::Camera()
{
	const float kRad		= 75.f;
	near_					= 0.1f;
	far_					= 1000.f;
	fov_					= RadianAssistant::TheNumRadian(kRad);
	pos_					= VectorAssistant::VGetZero();
	vel_					= VectorAssistant::VGetZero();
	target_vel_		= VectorAssistant::VGetZero();
	target_pos_		= VGet(0.f, 0.f, 25.f);

	Setting();
}

Camera::~Camera()
{

}

void Camera::Update()
{
	VECTOR dir	= VectorAssistant::VGetZero();
	VECTOR target_dir = VectorAssistant::VGetZero();
	
	if (FALSE)
	{
		if (CheckHitKey(KEY_INPUT_UP)) { dir = VAdd(dir, VGet(0, 1, 0)); target_dir = VAdd(target_dir, VGet(0, 0, 1)); }
		if (CheckHitKey(KEY_INPUT_DOWN)) { dir = VAdd(dir, VGet(0, -1, 0)); target_dir = VAdd(target_dir, VGet(0, 0, -1)); }
		if (CheckHitKey(KEY_INPUT_RIGHT)) { dir = VAdd(dir, VGet(1, 0, 0)); target_dir = VAdd(target_dir, VGet(1, 0, 0)); }
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			dir = VAdd(dir, VGet(-1, 0, 0)); target_dir = VAdd(target_dir, VGet(-1, 0, 0));
		}

		if (VSize(dir) > 0)
		{

		}
		if (CheckHitKey(KEY_INPUT_LSHIFT))
		{
			target_pos_ = VAdd(target_pos_, target_dir);
			pos_ = VAdd(pos_, target_dir);
		}
		else
		{
			pos_ = VAdd(pos_, dir);
		}
	}

	// brain‚©‚ç‚ÌˆÚ“®’l‚ðŽó‚¯Žæ‚é
	vel_				= Brain::GetInstance().GetVelocity();
	target_vel_	= Brain::GetInstance().GetTargetVelocity();
	Setting();
	
}

void Camera::Debug()
{
	DrawSphere3D(target_pos_, 1.f, 20.f, Color::kWhite, Color::kWhite, TRUE);
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "------------camera----------", Color::kWhite);
	Debug::GetInstance().Add();
	
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----pos-----", Color::kWhite);
	Debug::GetInstance().Add();
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "x : %.2f,y : %.2f,z : %.2f", pos_.x, pos_.y, pos_.z);
	Debug::GetInstance().Add();

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----target_pos-----", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(target_pos_);

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----dir-----", Color::kWhite);
	Debug::GetInstance().Add();
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "x : %.2f,y : %.2f,z : %.2f", dir_.x, dir_.y, dir_.z);
	Debug::GetInstance().Add();
}

void Camera::Setting()
{
	pos_ = VAdd(pos_, vel_);
	target_pos_ = VAdd(target_pos_, target_vel_);

	SetCameraNearFar(near_, far_);
	SetupCamera_Perspective(fov_);
	SetCameraPositionAndTarget_UpVecY(pos_, target_pos_);
	Effekseer_Sync3DSetting();
	dir_ = VectorAssistant::VGetDir(pos_, target_pos_);
}

VECTOR* Camera::GetPos()
{
	return &pos_;
}

VECTOR* Camera::GetTargetPos()
{
	return &target_pos_;
}