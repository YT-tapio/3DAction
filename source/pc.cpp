#include"DxLib.h"
#include"pc.h"
#include"vector_assistant.h"
#include"screen_size.h"

PC::PC()
{
	Init();
}

PC::~PC()
{

}

void PC::Init()
{
	// きーのpush状態を初期化
	for (int i = 0; i < kMaxKeyNum; i++)
	{
		key_state_[i].frame = 0;
		key_state_[i].time = 0;
		key_state_[i].pushing_time = 0.f;
		key_state_[i].releasing_time = 0.f;
		key_state_[i].is_pressed = FALSE;
	}
	//マウスのpush状態を初期化
	for (int i = 0; i < kMaxMouseButtonNum; i++)
	{
		mouse_state_[i].time				= 0;
		mouse_state_[i].frame			= 0;
		mouse_state_[i].pushing_time = 0.f;
		mouse_state_[i].releasing_time = 0.f;
		mouse_state_[i].is_pressed	= FALSE;
	}
	//マウスのposを初期化
	UpdateMousePos();
	mouse_wheel_rot_ = 0.f;
}

void PC::Debug()
{

}

void PC::Update()
{
	UpdateKey();
	UpdateMouseButton();
	UpdateMousePos();
	UpdateMouseWheel();
}

float PC::GetPushingTimeKey(int key_code)
{
	float time = -1.f;
	if (key_state_[key_code].is_pressed) 
	{ 
		time = key_state_[key_code].pushing_time;
	}
	return time;
}

float PC::GetPushingTimeMouseButton(int mouse_code)
{
	float time = -1.f;
	if (mouse_state_[mouse_code].is_pressed)
	{
		time = mouse_state_[mouse_code].pushing_time;
	}
	return time;
}

float PC::GetReleaseTimeKey(int key_code)
{
	float time = -1.f;
	if (!key_state_[key_code].is_pressed)
	{
		time = key_state_[key_code].releasing_time;
	}
	return time;
}

float PC::GetReleaseTimeMouseButton(int mouse_code)
{
	float time = -1.f;
	if (!mouse_state_[mouse_code].is_pressed)
	{
		time = mouse_state_[mouse_code].releasing_time;
	}
	return time;
}

const float PC::GetBeforePushingTimeKey(int key_code) const
{
	return key_state_[key_code].pushing_time;
}

const float PC::GetBeforeReleasingTimeKey(int key_code) const
{
	return key_state_[key_code].releasing_time;
}

const float PC::GetBeforePushingTimeMouseButton(int mouse_code) const
{
	return mouse_state_[mouse_code].pushing_time;
}

const float PC::GetBeforeReleasingTimeMouseButton(int mouse_code) const
{
	return mouse_state_[mouse_code].releasing_time;
}
const float PC::GetMouseWheelRot() const
{
	return mouse_wheel_rot_;
}

const VECTOR PC::GetMousePos() const
{
	return mouse_pos_;
}

const VECTOR PC::GetMouseVel() const
{
	return mouse_vel_;
}

const VECTOR PC::GetMouseDir() const
{
	return mouse_dir_;
}

void PC::UpdateKey()
{
	char all_keys[kMaxKeyNum] = {};
	GetHitKeyStateAll(all_keys);
	for (int i = 0; i < kMaxKeyNum; i++)
	{
		bool now_is_pressed = FALSE;	// 入力されているかのcheck
		auto key = all_keys[i];
		if (key == 1) { now_is_pressed = TRUE; }

		// 入力が違っていたら
		if (key_state_[i].is_pressed != now_is_pressed)
		{
			key_state_[i].is_pressed = now_is_pressed;
			key_state_[i].time = GetNowCount();//タイマーやフレームの更新
		}

		// 経過時間
		float elapsed_time = (GetNowCount() - key_state_[i].time) / 1000.f;
		if (key_state_[i].is_pressed)
		{
			key_state_[i].pushing_time = elapsed_time;
		}
		else
		{
			key_state_[i].releasing_time = elapsed_time;
		}
	}
}

void PC::UpdateMouseButton()
{
	for (int i = 0; i < kMaxMouseButtonNum; i++)
	{
		// 現在のどのマウスボタンかの判別
		int mouse_button_num	= GetMouseButtonNum(i);
		bool now_is_pressed		= (GetMouseInput() & mouse_button_num);
		if (now_is_pressed != mouse_state_[i].is_pressed)
		{
			mouse_state_[i].time		= GetNowCount();
			mouse_state_[i].frame	= 0;
			mouse_state_[i].is_pressed = now_is_pressed;
		}

		float elapsed_time = (GetNowCount() - mouse_state_[i].time) / 1000.f;
		if (mouse_state_[i].is_pressed)
		{
			mouse_state_[i].pushing_time = elapsed_time;
		}
		else
		{
			mouse_state_[i].releasing_time = elapsed_time;
		}
	}
}

void PC::UpdateMousePos()
{
	int mouse_x = 0;
	int mouse_y = 0;
	GetMousePoint(&mouse_x, &mouse_y);
	VECTOR screen_center_pos = VectorAssistant::VGet2D(float(kScreenWidth * 0.5f), float(kScreenHeight * 0.5f));
	mouse_pos_ = VectorAssistant::VGet2D(static_cast<float>(mouse_x), static_cast<float>(mouse_y));
	mouse_vel_ = VSub(screen_center_pos, mouse_pos_);
	if (fabs(mouse_vel_.x) < 1.5f) { mouse_vel_.x = 0.f; }
	if (fabs(mouse_vel_.y) < 1.5f) { mouse_vel_.y = 0.f; }
	mouse_dir_.z = 0.f;
	if (VSize(mouse_vel_) > 0.f){ mouse_dir_ = VNorm(mouse_vel_); }
	VECTOR mouse_diff = VectorAssistant::VGet2D(screen_center_pos.x - mouse_pos_.x, screen_center_pos.y - mouse_pos_.y);
	SetMousePoint(static_cast<int>(screen_center_pos.x), static_cast<int>(screen_center_pos.y));
}

void PC::UpdateMouseWheel()
{
	mouse_wheel_rot_ = GetMouseWheelRotVolF();
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