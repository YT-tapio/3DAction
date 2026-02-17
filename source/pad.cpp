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
		button_state_[i].time		= 0;
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
	right_stick_pos_	= VectorAssistant::VGet2D(pad.ThumbRX, pad.ThumbRY);

	// デッドゾーンの範囲内なら強制的に0にする
	if (left_stick_pos_.x < kDeadZone)	{ left_stick_pos_.x = 0.f; }
	if (left_stick_pos_.y < kDeadZone)	{ left_stick_pos_.y = 0.f; }
	if (right_stick_pos_.x < kDeadZone) { right_stick_pos_.x = 0.f; }
	if (right_stick_pos_.y < kDeadZone) { right_stick_pos_.y = 0.f; }
}

VECTOR Pad::GetRightStickDir()
{
	VECTOR dir = VectorAssistant::VGetZero();
	dir = VNorm(left_stick_pos_);
	if (VSize(dir) > 0) { dir = VNorm(dir); }
	return dir;
}

VECTOR Pad::GetLeftStickDir()
{
	VECTOR dir = VectorAssistant::VGetZero();
	if(VSize(right_stick_pos_) > 0)
	dir = VNorm(right_stick_pos_);
	return dir;
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