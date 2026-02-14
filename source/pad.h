#pragma once
#include"input_state.h"

const int kMaxButtonNum = 16;

class Pad
{
public:

	
	Pad(int pad_num);

	~Pad();

	void Init();

	void Update();

private:

	InputState button_state_[kMaxButtonNum];
	InputState left_stick_x_state_;
	InputState left_stick_y_state_;
	InputState right_stick_x_state_;
	InputState right_stick_y_state_;

	int pad_num_;

	void ButtonUpdate(XINPUT_STATE pad);

};