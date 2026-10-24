#include<functional>
#include"DxLib.h"
#include"title_camera.h"

TitleCamera::TitleCamera(VECTOR* pos, VECTOR* target_pos, std::function<VECTOR()> get_head_pos)
	: VirtualCameraBase(pos,target_pos)
	, phase_(Phase::first)
	, get_head_pos_(get_head_pos)
{

}

TitleCamera::~TitleCamera()
{

}

void TitleCamera::Awake()
{

}

void TitleCamera::Init()
{

}

void TitleCamera::Update()
{
	switch (phase_)
	{
	case Phase::first:
		FirstPhaseUpdate();
		break;

	case Phase::second:
		SecondPhaseUpdate();
		break;

	case Phase::third:
		ThirdPhaseUpdate();
		break;
	}
}

void TitleCamera::FirstPhaseUpdate()
{
	// ƒvƒŒƒCƒ„[‚ğŒ©‚È‚ª‚ç’Ç”ö‚·‚é
	auto head_pos = get_head_pos_();

	auto main_camera_pos = *main_camera_pos_;
	auto main_camera_target_pos = *main_camera_target_pos_;

	target_vel_ = VSub(head_pos, main_camera_target_pos);
	vel_ = target_vel_;
	
}

void TitleCamera::SecondPhaseUpdate()
{

}

void TitleCamera::ThirdPhaseUpdate()
{

}