#pragma once

class ConditionTimer;
class ButtonUI;
class StringUI;

class StartGuide
{
public:

	StartGuide();

	~StartGuide();

	void Awake();

	void Init();

	void Update();

	void Draw();

private:

	// •\Ž¦‚·‚é
	void DrawButtonAndString();

private:

	const float kMaxBlendPercent = 255.f;

	const float kSpeed = 2.9f;

	std::shared_ptr<ConditionTimer> timer_;
	std::shared_ptr<ButtonUI> button_ui_;
	std::shared_ptr<StringUI> string_ui_;
	
	float target_blend_percent_;
	float current_blend_percent_;

};