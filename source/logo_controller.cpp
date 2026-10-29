#include<memory>
#include"DxLib.h"
#include"logo_controller.h"
#include<string>
#include<functional>
#include"draw_2d.h"
#include"vector_assistant.h"
#include"screen_size.h"
#include"condition_timer.h"
#include"lerp.h"
LogoController::LogoController()
{
	handle_ = LoadGraph("data/ui/title/title_logo.png");
	if (handle_ == -1)
	{
		printfDx("ÉÇÉfÉãì«Ç›çûÇ›ÉGÉâÅ[\n");
	}

	const VECTOR kPos = VectorAssistant::VGet2D(static_cast<float>(kScreenWidth * 0.5f),
		700.f);

	const float kSize = 0.7f;
	size_up_timer_ = std::make_shared<ConditionTimer>(1.f);
	pos_ = kPos;
	size_ = 0.f;
	is_active_ = TRUE;
}

LogoController::~LogoController()
{
	DeleteGraph(handle_);
}

void LogoController::Awake()
{

}

void LogoController::Init()
{
	
}

void LogoController::Update()
{
	if (!is_active_) { return; }
	size_up_timer_->Update();

	if (size_up_timer_->GetIsEnd())
	{
		size_ = kTargetSize;
	}
	else
	{
		// ÇæÇÒÇæÇÒÇ∆ëÂÇ´Ç≠Ç»ÇÈ
		auto ratio = size_up_timer_->GetRatio();
		auto diff = kTargetSize - size_;
		size_ += diff * ratio;
	}
}

void LogoController::Draw()
{
	if (!is_active_) { return; }
	Draw2D::RotaGraph(pos_, size_, 0.f, handle_, TRUE);
}

void LogoController::Active()
{
	is_active_ = TRUE;
}