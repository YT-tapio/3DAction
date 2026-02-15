#include"DxLib.h"
#include"pad.h"


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
	for (int i = 0; i < kMaxMouseNum; i++)
	{
		button_state_[i].frame		= 0;
		button_state_[i].time		= 0;
		button_state_[i].is_pressed = FALSE;
	}
}

void Pad::Update()
{
	XINPUT_STATE pad = {};
	GetJoypadXInputState(pad_num_, &pad);
}

void Pad::ButtonUpdate(XINPUT_STATE pad)
{
	for (int i = 0; i < kMaxMouseNum; i++)
	{
		bool now_is_pressed = (pad.Buttons[i] == 1);
		
		// “ü—Í‚ªXV‚³‚ê‚Ä‚¢‚½‚ç
		if (now_is_pressed != button_state_[i].is_pressed)
		{
			button_state_[i].frame		= 0;
			button_state_[i].time		= GetNowCount();
			button_state_[i].is_pressed = now_is_pressed;
		}
	}
}