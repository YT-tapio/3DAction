#include"DxLib.h"
#include"pad.h"
#include"vector_assistant.h"

Pad::Pad(int pad_num)
	:pad_num_(pad_num)
{
	Init();
}

Pad::~Pad()
{

}

void Pad::Init()
{
	for (int i = 0; i < kMaxPadButtonNum; i++)
	{
		button_state_[i].frame		= 0;
		button_state_[i].time			= 0;
		button_state_[i].pushing_time		= 0.f;
		button_state_[i].releasing_time = 0.f;
		button_state_[i].is_pressed = FALSE;
	}
	left_stick_pos_		= VectorAssistant::VGetZero();
	right_stick_pos_	= VectorAssistant::VGetZero();
}

void Pad::Update()
{
	XINPUT_STATE pad = {};
	GetJoypadXInputState(pad_num_, &pad);
	ButtonUpdate(pad);
	left_stick_pos_		= VectorAssistant::VGet2D(pad.ThumbLX, pad.ThumbLY);
	right_stick_pos_		= VectorAssistant::VGet2D(pad.ThumbRX, pad.ThumbRY);

	// デッドゾーンの範囲内なら強制的に0にする
	CheckDeadZone();
	left_stick_pos_.z = 0.f;
	right_stick_pos_.z = 0.f;
}

float Pad::GetPushingTimeButton(int pad_code)
{
	float pushing_time = -1.f;

	if (button_state_[pad_code].is_pressed)
	{
		int now_time = GetNowCount();
		pushing_time = now_time - button_state_[pad_code].time;
		pushing_time = pushing_time / 1000.f;
		button_state_[pad_code].pushing_time = pushing_time;
	}
	return pushing_time;
}

float Pad::GetReleaseTimeButton(int pad_code)
{
	float release_time = -1.f;

	if (!button_state_[pad_code].is_pressed)
	{
		int now_time = GetNowCount();
		release_time = now_time - button_state_[pad_code].time;
		release_time = release_time / 1000.f;
		button_state_[pad_code].releasing_time = release_time;
	}
	return release_time;
}

float Pad::GetLeftStickRatio()
{
	float left_stick_ratio = 0.f;
	left_stick_ratio = VSize(left_stick_pos_) / kMaxStickSizeMax;
	return left_stick_ratio;
}

float Pad::GetRightStickRatio()
{
	float right_stick_ratio = 0.f;
	right_stick_ratio = VSize(right_stick_pos_) / kMaxStickSizeMax;
	return right_stick_ratio;
}

VECTOR Pad::GetRightStickDir()
{
	VECTOR dir = VectorAssistant::VGetZero();
	if (VSize(right_stick_pos_) > 0) { dir = VNorm(right_stick_pos_); }
	return dir;
}

VECTOR Pad::GetLeftStickDir()
{
	VECTOR dir = VectorAssistant::VGetZero();
	if(VSize(left_stick_pos_) > 0){ dir = VNorm(left_stick_pos_); }
	return dir;
}

VECTOR Pad::GetRightStickVel()
{
	VECTOR right_stick_vel = VectorAssistant::VGetZero();

	return right_stick_vel;
}

VECTOR Pad::GetLeftStickVel()
{
	VECTOR left_stick_vel = VectorAssistant::VGetZero();

	return left_stick_vel;
}

const float Pad::GetBeforePushingTimeButton(int pad_code) const
{
	return button_state_[pad_code].pushing_time;
}

const float Pad::GetBeforeReleasingTimeButton(int pad_code) const
{
	return button_state_[pad_code].releasing_time;
}

void Pad::ButtonUpdate(XINPUT_STATE pad)
{
	for (int i = 0; i < kMaxPadButtonNum; i++)
	{
		bool now_is_pressed = (pad.Buttons[i] == 1);
		
		// 入力が更新されていたら
		if (now_is_pressed != button_state_[i].is_pressed)
		{
			button_state_[i].frame		= 0;
			button_state_[i].time		= GetNowCount();
			button_state_[i].is_pressed = now_is_pressed;
		}
	}
}

void Pad::CheckDeadZone()
{
	if (left_stick_pos_.x < kDeadZone && left_stick_pos_.x > -kDeadZone) { left_stick_pos_.x = 0.f; }
	if (left_stick_pos_.y < kDeadZone && left_stick_pos_.y > -kDeadZone) { left_stick_pos_.y = 0.f; }

	if (right_stick_pos_.x < kDeadZone && right_stick_pos_.x > -kDeadZone) { right_stick_pos_.x = 0.f; }
	if (right_stick_pos_.y < kDeadZone && right_stick_pos_.y > -kDeadZone) { right_stick_pos_.y = 0.f; }
}