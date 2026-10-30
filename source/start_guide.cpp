#include<string>
#include<memory>
#include"DxLib.h"
#include"start_guide.h"
#include<functional>
#include"draw_2D.h"
#include"condition_timer.h"
#include"button_ui.h"
#include"config_name.h"
#include"vector_assistant.h"
#include"start_string_ui.h"
#include"lerp.h"
#include"FPS.h"

StartGuide::StartGuide()
	: current_blend_percent_(255.f)
	, target_blend_percent_(0.f)
{
	timer_ = std::make_shared<ConditionTimer>(3.f);
	const VECTOR kPos = VectorAssistant::VGet2D(428.f, 793.f);
	const float kSize = 0.2f;
	button_ui_ = std::make_shared<ButtonUI>(ConfigName::play, kPos, kSize, nullptr);
	string_ui_ = std::make_shared<StartStringUI>();
}

StartGuide::~StartGuide()
{

}

void StartGuide::Awake()
{
	timer_->Init();
	timer_->ReStart();
}

void StartGuide::Init()
{
	timer_->Init();
	timer_->ReStart();
}

void StartGuide::Update()
{
	auto speed = kSpeed * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS();
	current_blend_percent_ = Lerp::Lerpf(current_blend_percent_, target_blend_percent_, speed);
	if(current_blend_percent_ == target_blend_percent_)
	{
		if (target_blend_percent_ == kMaxBlendPercent)
		{
			target_blend_percent_ = 0.f;
		}
		else
		{
			target_blend_percent_ = kMaxBlendPercent;
		}
	}
}

void StartGuide::Draw()
{
	auto draw_func = [this]() -> void
		{
			DrawButtonAndString();
		};

	Draw2D::Blend(draw_func, static_cast<int>(current_blend_percent_));
}

void StartGuide::DrawButtonAndString()
{
	button_ui_->Draw();
	string_ui_->Draw();
}