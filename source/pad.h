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

private:

	static const int kMaxPadButtonNum = 16;

	InputState button_state_[kMaxPadButtonNum];
	InputState left_stick_x_state_;
	InputState left_stick_y_state_;
	InputState right_stick_x_state_;
	InputState right_stick_y_state_;

	int pad_num_;

	void ButtonUpdate(XINPUT_STATE pad);

};