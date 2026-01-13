#include<iostream>
#include"DxLib.h"
#include"debug.h"
#include"color.h"

void Debug::Reset()
{
	num_ = 0;
}

void Debug::Update()
{
	//ここでデバッグの切り替え

	static bool is_push = FALSE;


	if (CheckHitKey(KEY_INPUT_N))
	{
		if (!is_push)
		{
			is_disp_ = !is_disp_;
		}
		is_push = TRUE;
	}
	else
	{
		is_push = FALSE;
	}


}

void Debug::Add()
{
	num_++;
}

void Debug::DrawVector(const VECTOR& vec)
{
	int now_line_num = num_ * kLineSize;
	DrawFormatString(0, now_line_num, Color::kWhite, "x : %.2f, y : %.2f, z : %.2f", vec.x, vec.y, vec.z);
	Add();
}

const int Debug::GetLineSize() const
{
	return kLineSize;
}

const int Debug::GetNum() const
{
	return num_;
}

const int Debug::GetNowLineSize() const
{
	int now_line_num = num_ * kLineSize;
	return now_line_num;
}

const bool Debug::GetIsDisp() const
{
	return is_disp_;
}


Debug::Debug()
{
	num_ = 0;
	is_disp_ = TRUE;
}