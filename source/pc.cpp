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
		key_state_[i].frame = 0;
		key_state_[i].time = 0;
		key_state_[i].is_pressed = FALSE;
	}
	for (int i = 0; i < kMaxMouseNum; i++)
	{
		mouse_state_[i].time				= 0;
		mouse_state_[i].frame			= 0;
		mouse_state_[i].is_pressed	= FALSE;
	}
}

void PC::Debug()
{

}

void PC::Update()
{
	KeyUpdate();
	MouseUpdate();
}

float PC::GetPushingTimeKey(int key_code)
{
	float num = -1.f;

	if (key_state_[key_code].is_pressed) 
	{ 
		int now_time = GetNowCount();
		num = now_time - key_state_[key_code].time;
		num = num / 1000.f;
	}
	return num;
}

float PC::GetPushingTimeMouseButton(int mouse_code)
{
	float num = -1.f;

	if (mouse_state_[mouse_code].is_pressed)
	{
		int now_time = GetNowCount();
		num = now_time - mouse_state_[mouse_code].time;
		num = num / 1000.f;
	}

	return num;
}

float PC::GetReleaseTimeKey(int key_code)
{
	float num = -1.f;

	if (!key_state_[key_code].is_pressed)
	{
		int now_time = GetNowCount();
		num = now_time - key_state_[key_code].time;
		num = num / 1000.f;
	}
	return num;
}

float PC::GetReleaseTimeMouseButton(int mouse_code)
{
	float time = -1.f;
	if (!mouse_state_[mouse_code].is_pressed)
	{
		int now_time = GetNowCount();
		time = now_time - mouse_state_[mouse_code].time;
		time = time / 1000;
	}

	return time;
}

void PC::KeyUpdate()
{
	char all_keys[kMaxKeyNum] = {};
	CheckHitKeyAll(*all_keys);
	for (int i = 0; i < kMaxKeyNum; i++)
	{
		bool now_is_pressed = (all_keys[i] == 1);	// 入力されているかのcheck

		// 入力が違っていたら
		if (key_state_[i].is_pressed != now_is_pressed)
		{
			key_state_[i].is_pressed = now_is_pressed;
			key_state_[i].time = GetNowCount();//タイマーやフレームの更新
		}
	}
}

void PC::MouseUpdate()
{
	for (int i = 0; i < kMaxMouseNum; i++)
	{
		// 現在のどのマウスボタンかの判別
		int mouse_button_num	= GetMouseButtonNum(i);
		bool now_is_pressed		= ((GetMouseInput() & mouse_button_num) == 1);
		if (now_is_pressed == mouse_state_[i].is_pressed)
		{
			mouse_state_[i].time		= GetNowCount();
			mouse_state_[i].frame	= 0;
			mouse_state_[i].is_pressed = now_is_pressed;
		}
	}
}

int PC::GetMouseButtonNum(int mouse_num)
{
	int num = -1;

	switch (mouse_num)
	{
	case 0:
		num = MOUSE_INPUT_LEFT;
		break;
	case 1:
		num = MOUSE_INPUT_RIGHT;
		break;
	case 2:
		num = MOUSE_INPUT_MIDDLE;
		break;
	case 3:
		num = MOUSE_INPUT_4;
		break;
	case 4:
		num = MOUSE_INPUT_5;
		break;
	}

	return num;
}