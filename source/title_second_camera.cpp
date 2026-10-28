#include"DxLib.h"
#include"title_second_camera.h"
#include"vector_assistant.h"

TitleSecondCamera::TitleSecondCamera(VECTOR* pos, VECTOR* target_pos)
	: VirtualCameraBase(pos,target_pos)
{

}

TitleSecondCamera::~TitleSecondCamera()
{

}

void TitleSecondCamera::Awake()
{

}

void TitleSecondCamera::Init()
{

}

void TitleSecondCamera::Update()
{
	// ÉvÉåÉCÉÑÅ[ÇÃì|ÇÍÇÈèuä‘Çå©ÇÈ
	auto main_camera_pos = *main_camera_pos_;
	auto main_camera_target_pos = *main_camera_target_pos_;
	vel_ = VSub(kMyPos,main_camera_pos);
	target_vel_ = VSub(kMyTargetPos, main_camera_target_pos);
}