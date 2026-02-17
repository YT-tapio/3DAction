#pragma once
#include"input_state.h"
#include"input_interface.h"


class Pad : public IInput
{
public:

	Pad(int pad_num);

	~Pad() override;

	void Init();

	void Update() override;

	VECTOR GetRightStickDir();

	VECTOR GetLeftStickDir();

private:

	static const int kMaxPadButtonNum	= 16;

	static const int kMaxStickSizeMax	= 32767;
	static const int kDeadZone			= 10000;

	InputState button_state_[kMaxPadButtonNum];
	InputState left_stick_x_state_;
	InputState left_stick_y_state_;
	InputState right_stick_x_state_;
	InputState right_stick_y_state_;

	VECTOR left_stick_pos_;
	VECTOR right_stick_pos_;

	int pad_num_;

	void ButtonUpdate(XINPUT_STATE pad);

};