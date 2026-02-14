#include"DxLib.h"
#include"pc.h"

PC::PC()
{

}

PC::~PC()
{

}

void PC::Init()
{
	for (int i = 0; i < kMaxKeyNum; i++)
	{
		state_[i].frame = 0;
		state_[i].time = 0;
		state_[i].is_pressed = FALSE;
	}
}

void PC::Update()
{
	char all_keys[kMaxKeyNum] = {};
	CheckHitKeyAll(*all_keys);
	for (int i = 0; i < kMaxKeyNum; i++)
	{
		bool now_is_pressed = (all_keys[i] == 1);	// 入力されているかのcheck

		// 入力が違っていたら
		if (state_[i].is_pressed != now_is_pressed)
		{
			state_[i].is_pressed = now_is_pressed;
			state_[i].time = GetNowCount();//タイマーやフレームの更新
		}

	}
}


float PC::GetPushingTimeKey(int key_code)
{
	float num = -1.f;

	if (state_[key_code].is_pressed) 
	{ 
		int now_time = GetNowCount();
		num = now_time - state_[key_code].time;
		num = num / 1000.f;
	}
	return num;
}

float PC::GetReleaseTimeKey(int key_code)
{
	float num = -1.f;

	if (!state_[key_code].is_pressed)
	{
		int now_time = GetNowCount();
		num = now_time - state_[key_code].time;
		num = num / 1000.f;
	}
	return num;
}