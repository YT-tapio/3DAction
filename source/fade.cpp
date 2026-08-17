#include<memory>
#include"DxLib.h"
#include"fade.h"
#include<functional>
#include<string>
#include"draw_2D.h"
#include"screen_size.h"
#include"vector_assistant.h"
#include"color.h"

void Fade::Awake()
{
	start_ = FALSE;
	is_finished_ = FALSE;
	fade_color_type_ = FadeColorType::kNone;
	fade_type_ = FadeType::kNone;
	timer_ = std::make_shared<VariableTimer>(1.f);
}

void Fade::Update()
{
	if (!start_) 
	{
		is_finished_ = FALSE;
		return;
	}

	timer_->Update();
	float timer_ratio = 0.f;

	switch (fade_type_)
	{
	case FadeType::kFadeIn:
		timer_ratio = timer_->GetRatio();
		break;

	case FadeType::kFadeOut:
		timer_ratio = 1 - timer_->GetRatio();
		break;
	}

	alpha_ = kMaxAlphaValue * timer_ratio;
	if (timer_->GetIsEnd())
	{
		start_ = FALSE;
		is_finished_ = TRUE;
	}
}

void Fade::Draw()
{
	auto function = [this]() -> void
		{
			DrawBox();
		};
	Draw2D::Blend(function, alpha_);
}

void Fade::StartFadeIn(const float& time, FadeColorType type)
{
	start_ = TRUE;
	is_finished_ = FALSE;
	fade_color_type_ = type;

	timer_->Stop();
	timer_->ChangeMaxTime(time);
	timer_->ReStart();
	fade_type_ = FadeType::kFadeIn;
}

void Fade::StartFadeOut(const float& time)
{
	start_ = TRUE;
	is_finished_ = FALSE;

	timer_->Stop();
	timer_->ChangeMaxTime(time);
	timer_->ReStart();
	fade_type_ = FadeType::kFadeOut;
}

const bool Fade::IsFinished() const
{
	return is_finished_;
}

Fade::Fade()
{

}

void Fade::DrawBox()
{
	auto pos = VectorAssistant::VGet2D(float(kScreenWidth) * 0.5f, float(kScreenHeight) * 0.5f);
	unsigned int color = -1;
	switch (fade_color_type_)
	{
	case FadeColorType::kWhite:
		color = GetColor(255, 255, 255);
		break;

	case FadeColorType::kBlack:
		color = GetColor(0, 0, 0);
		break;
	}
	Draw2D::Box(pos, kScreenWidth, kScreenHeight, color, TRUE);
}