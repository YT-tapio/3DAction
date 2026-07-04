#include"change_method.h"
#include"DxLib.h"
#include"hit_red_body.h"


HitRedBody::HitRedBody(int handle)
	: handle_(handle)
	, red_ratio_(0.f)
{

}

HitRedBody::~HitRedBody()
{

}

void HitRedBody::Init()
{
	red_ratio_ = 0.f;
}

void HitRedBody::Update()
{
	if (!is_change_) { return; }

	switch (change_method_)
	{
	case ChangeMethod::kMoment:
		//red_ratio_ = 
		break;

	case ChangeMethod::kLerp:

		break;

	case ChangeMethod::kDamp:

		break;
	}

}

void HitRedBody::DoRedColor()
{
	if(is_change_)
	MV1SetAmbColorScale(handle_, GetColorF(red_ratio_, 0.f, 0.f, 1.f));
}

void HitRedBody::Request(const ChangeMethod change_method)
{
	change_method_	= change_method;
	is_change_		= TRUE;
}