#include<memory>
#include<string>
#include"DxLib.h"
#include"string_ui.h"
#include"damage_ui.h"
#include"vector_assistant.h"
#include"condition_timer.h"
#include"lerp.h"
#include<functional>
#include"draw_2d.h"


DamageUI::DamageUI(int font_handle)
	: stop_timer_(std::make_shared<ConditionTimer>(9.f))
	, pos_(VectorAssistant::VGetZero())
	, spawn_pos_(VectorAssistant::VGetZero())
	, font_handle_(font_handle)
	, default_up_speed_(4.f)
	, current_up_speed_(0.f)
	, damage_(0.f)
	, alpha_value_(255.f)
	, is_jump_(FALSE)
	, is_active_(FALSE)
{
	
}

DamageUI::~DamageUI()
{

}

void DamageUI::Init()
{
	pos_ = VectorAssistant::VGetZero();
	spawn_pos_ = VectorAssistant::VGetZero();
	current_up_speed_ = 0.f;
	damage_ = 0.f;
	is_jump_ = TRUE;
	is_active_ = FALSE;
	stop_timer_->Init();
}

void DamageUI::Update()
{
	// スポーンしてからジャンプさせる
	if (is_jump_)
	{
		current_up_speed_ -= 1.f;
		pos_.y -= current_up_speed_;

		if (spawn_pos_.y < pos_.y)
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
			alpha_value_ = Lerp::Dampf(alpha_value_, 0.f, 0.7f);
			pos_.y -= 2.f;
		}
	}
}

const void DamageUI::Draw() const
{
	if (alpha_value_ == 0.f) { return; }

	auto function = [this]() -> void
		{
			Draw2D::ExtendFormatStringToHandle(pos_, 2.f,2.f,"%d", GetColor(0, 0, 0), font_handle_, static_cast<int>(damage_));
		};

	Draw2D::Blend(function, alpha_value_);
}

void DamageUI::Spawn(const VECTOR& pos, const float& damage)
{
	spawn_pos_ = pos;
	pos_ = pos;
	damage_ = damage;
	current_up_speed_ = default_up_speed_;
	is_jump_ = TRUE;
	is_active_ = TRUE;
	stop_timer_->ReStart();
}

const bool DamageUI::GetIsActive() const
{
	return is_active_;
}