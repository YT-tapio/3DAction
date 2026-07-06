#include<memory>
#include"change_method.h"
#include"DxLib.h"
#include"hit_red_body.h"
#include"lerp.h"
#include"condition_timer.h"
#include"variable_timer.h"

HitRedBody::HitRedBody(int handle)
	: is_change_(FALSE)
	, change_method_(ChangeMethod::kMoment)
	, handle_(handle)
	, red_ratio_(1.f)
	, target_red_ratio_(2.f)
	, validity_timer_(std::make_shared<VariableTimer>(0.f))
{

}

HitRedBody::~HitRedBody()
{

}

void HitRedBody::Init()
{
	red_ratio_ = 0.f;
	is_change_ = FALSE;
}

void HitRedBody::Update()
{
	if (!is_change_) { return; }

	switch (change_method_)
	{
	case ChangeMethod::kMoment:
		
		red_ratio_ = target_red_ratio_;

		break;

	case ChangeMethod::kLerp:

		red_ratio_ = Lerp::Lerpf(red_ratio_,target_red_ratio_,0.5f);

		break;

	case ChangeMethod::kDamp:

		red_ratio_ = Lerp::Dampf(red_ratio_,target_red_ratio_,0.5f);

		break;
	}

	if (red_ratio_ == target_red_ratio_)
	{
		if (red_ratio_ == 1.f)
		{
			is_change_ = FALSE;
			return;
		}
		validity_timer_->Update();
		// ターゲットを変える
		if (validity_timer_->GetIsEnd())
		{
			target_red_ratio_ = 1.f;
		}
	}
}

void HitRedBody::DoRedColor()
{
	if (!is_change_)
	{
		// もともとの色に戻す
		MV1SetAmbColorScale(handle_, GetColorF(1, 1.f, 1.f, 1.f));
		return;
	}
	if (red_ratio_ == 0.f)	{ return; }
	MV1SetAmbColorScale(handle_, GetColorF(red_ratio_, 1.f, 1.f, 1.f));
}

void HitRedBody::Request(const ChangeMethod change_method,const float time)
{
	change_method_	= change_method;
	is_change_		= TRUE;
	target_red_ratio_ = 4.f;
	validity_timer_->Stop();
	validity_timer_->ChangeMaxTime(time);
	validity_timer_->Start();
}