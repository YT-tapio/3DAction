#include<memory>
#include"DxLib.h"
#include"shake.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"vector_assistant.h"
#include"random.h"

Shake::Shake()
	: timer_(std::make_shared<VariableTimer>(0.f))
	, shake_vel_(VectorAssistant::VGetZero())
	, power_(0.f)
	, is_active_(FALSE)
{

}

Shake::~Shake()
{

}

void Shake::Init()
{

}

void Shake::Update()
{
	// 起動していないときは非アクティブ
	if (!is_active_) { return;}
	timer_->Update();
	float reverce_ratio = 1 - timer_->GetRatio();
	shake_vel_ = VScale(GetRandomShakeVel(), reverce_ratio);

	if (timer_->GetIsEnd())
	{
		is_active_ = FALSE;
		shake_vel_ = VectorAssistant::VGetZero();
	}

}

void Shake::Active(const float& power, const float& time)
{
	is_active_ = TRUE;
	power_ = power;
	timer_->Stop();
	timer_->ChangeMaxTime(time);
	timer_->ReStart();
}

const VECTOR Shake::GetShakeVel() const
{
	return shake_vel_;
}

const VECTOR Shake::GetRandomShakeVel() const
{
	VECTOR random_shake_vel = VectorAssistant::VGetZero();
	random_shake_vel.x = GetUniformRandom(-power_, power_);
	random_shake_vel.y = GetUniformRandom(-power_, power_);
	random_shake_vel.z = GetUniformRandom(-power_, power_);
	return random_shake_vel;
}