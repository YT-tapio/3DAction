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

	float GetPushingTimeButton(int pad_code);

	float GetReleaseTimeButton(int pad_code);

	float GetLeftStickRatio();

	float GetRightStickRatio();

	VECTOR GetRightStickDir();

	VECTOR GetLeftStickDir();

	VECTOR GetRightStickVel();

	VECTOR GetLeftStickVel();

	const float GetBeforePushingTimeButton(int pad_code) const;

	const float GetBeforeReleasingTimeButton(int pad_code) const;

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

	void CheckDeadZone();

};