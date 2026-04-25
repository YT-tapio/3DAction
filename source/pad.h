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

	static const int kMaxStickSize		= 32767;
	static const int kDeadZone			= 10000;
	static const int kMaxTrigger			= 255;

	InputState button_state_[kMaxPadButtonNum];
	VECTOR left_stick_pos_;
	VECTOR right_stick_pos_;

	int pad_num_;
	int left_trigger_;
	int right_trigger_;

	void ButtonUpdate(XINPUT_STATE pad);

	void CheckDeadZone();

};