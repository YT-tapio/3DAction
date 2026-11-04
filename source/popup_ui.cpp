#include<memory>
#include"DxLib.h"
#include"popup_ui.h"
#include"time.h"
#include"condition_timer.h"
#include"lerp.h"
#include<string>
#include<functional>
#include"draw_2D.h"
#include"random.h"

PopupUI::PopupUI()
	: stop_timer_(std::make_shared<ConditionTimer>(2.f))
	, time_(std::make_shared<Time>())
	, pos_(VectorAssistant::VGetZero())
	, spawn_pos_(VectorAssistant::VGetZero())
	, handle_(-1)
	, default_up_speed_(2.f)
	, current_up_speed_(0.f)
	, out_up_speed_(0.4f)
	, alpha_value_(255.f)
	, is_jump_(FALSE)
	, is_active_(FALSE)
{

}

PopupUI::~PopupUI()
{

}

void PopupUI::Init()
{
	pos_ = VectorAssistant::VGetZero();
	spawn_pos_ = VectorAssistant::VGetZero();
	current_up_speed_ = 0.f;
	is_jump_ = TRUE;
	is_active_ = FALSE;
	stop_timer_->Init();
	time_->Init();
}

void PopupUI::Update()
{
	if (!is_active_) { return; }
	if (alpha_value_ < 0.1f)
	{
		is_active_ = FALSE;
	}
	time_->Update();
	// スポーンしてからジャンプさせる
	if (is_jump_)
	{
		current_up_speed_ -= 0.5f * time_->GetFPSRate();
		pos_.y += current_up_speed_;

		if (spawn_pos_.y > pos_.y)
		{
			spawn_pos_.y = pos_.y;
			is_jump_ = FALSE;
		}
	}
	else
	{
		// 
		if (!stop_timer_->GetIsEnd()) { stop_timer_->Update(); }
		if (stop_timer_->GetIsEnd())
		{
			// だんだんと消えるかつ上昇していく
			alpha_value_ = Lerp::Dampf(alpha_value_, 0.f, 0.5f * time_->GetFPSRate());
			pos_.y += out_up_speed_ * time_->GetFPSRate();
		}
	}
}

const void PopupUI::Draw() const
{
	if (alpha_value_ == 0.f) { return; }

	auto draw_function = [this]() -> void
		{
			DrawBillboard3D(pos_, 0.5f, 0.5f, size_, 0.f, handle_, TRUE);
		};

	Draw2D::Blend(draw_function, alpha_value_);
}

void PopupUI::Spawn(const VECTOR pos,int handle,const int& size)
{
	size_ = size;
	handle_ = handle;
	pos_ = spawn_pos_;
	current_up_speed_ = default_up_speed_;
	alpha_value_ = 255.f;
	is_jump_ = TRUE;
	is_active_ = TRUE;
	stop_timer_->ReStart();
}

const bool PopupUI::GetIsActive() const
{
	return is_active_;
}

VECTOR PopupUI::RandomSpawnPos(const VECTOR& pos)
{
	VECTOR random_pos = VectorAssistant::VGetZero();
	int random_width = GetUniformRandom(-10, 10);
	int random_height = -GetUniformRandom(-3, 0);
	random_pos = VAdd(pos, VectorAssistant::VGet2D(random_width, random_height));;
	return random_pos;
}