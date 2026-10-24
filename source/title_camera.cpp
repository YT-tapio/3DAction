#include"DxLib.h"
#include"title_camera.h"

TitleCamera::TitleCamera(VECTOR* pos, VECTOR* target_pos)
	: VirtualCameraBase(pos,target_pos)
	, phase_(Phase::first)
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
		FirstUpdate();
		break;

	case Phase::second:
		SecondUpdate();
		break;

	case Phase::third:
		ThirdUpdate();
		break;
	}
}

void TitleCamera::FirstUpdate()
{

}

void TitleCamera::SecondUpdate()
{

}

void TitleCamera::ThirdUpdate()
{

}