#pragma once

class SubScreen;
class ButtonUI;
class AvoidStringUI;
class StringUI;
class DashStringUI;
class MoveStringUI;
class MoveCameraStringUI;

class InputControlUI
{
public:

	InputControlUI();

	~InputControlUI();

	void Awake();

	void Init();

	void Update();

	void Draw();

private:

	// ÉXÉNÉäÅ[ÉìÇ…ï`âÊ
	void DrawSubScreen();

private:

	std::shared_ptr<SubScreen> screen_;
	std::vector<std::shared_ptr<StringUI>> string_uis_;
	std::vector<std::shared_ptr<ButtonUI>> button_uis_;

	int move_input_handle_;
	int move_camera_input_handle_;
	VECTOR screen_pos_;
};