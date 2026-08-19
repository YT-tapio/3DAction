#include"DxLib.h"
#include"lose_camera.h"

LoseCamera::LoseCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos)
	: VirtualCameraBase(main_camera_pos, main_camera_target_pos)
{

}

LoseCamera::~LoseCamera()
{

}

void LoseCamera::Awake()
{

}

void LoseCamera::Init()
{
	vel_ = VGet(0.f, 0.f, 0.f);
	target_vel_ = VGet(0.f, 0.f, 0.f);
}

void LoseCamera::Update()
{
	
}