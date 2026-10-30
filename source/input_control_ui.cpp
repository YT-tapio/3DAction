#include<memory>
#include<string>
#include<vector>
#include"DxLib.h"
#include"input_control_ui.h"
#include"vector_assistant.h"
#include<functional>
#include"draw_2d.h"
#include"sub_screen.h"
#include"button_ui.h"
#include"config_name.h"
#include"avoid_string_ui.h"
#include"dash_string_ui.h"
#include"move_string_ui.h"
#include"move_camera_string_ui.h"
#include"target_string_ui.h"
#include"jump_string_ui.h"

InputControlUI::InputControlUI()
	: screen_pos_(VectorAssistant::VGet2D(1200.f,860.f))
{
	screen_ = std::make_shared<SubScreen>(900, 100);
	string_uis_.emplace_back(std::make_shared<AvoidStringUI>());
	string_uis_.emplace_back(std::make_shared<DashStringUI>());
	string_uis_.emplace_back(std::make_shared<MoveStringUI>());
	string_uis_.emplace_back(std::make_shared<MoveCameraStringUI>());
	string_uis_.emplace_back(std::make_shared<TargetStringUI>());
	string_uis_.emplace_back(std::make_shared<JumpStringUI>());
	const float kAButtonSize = 0.065f;
	const float kLeftButtonSize = 0.071f;
	button_uis_.emplace_back(std::make_shared<ButtonUI>(ConfigName::avoid, VectorAssistant::VGet2D(205.f, 50.f), kAButtonSize, nullptr));
	button_uis_.emplace_back(std::make_shared<ButtonUI>(ConfigName::dash, VectorAssistant::VGet2D(364.f, 50.f), kAButtonSize, nullptr));
	button_uis_.emplace_back(std::make_shared<ButtonUI>(ConfigName::jump, VectorAssistant::VGet2D(570.f, 50.f), kAButtonSize, nullptr));
	button_uis_.emplace_back(std::make_shared<ButtonUI>(ConfigName::lock_on, VectorAssistant::VGet2D(688.f, 50.f), kLeftButtonSize, nullptr));
	//button_uis_.emplace_back(ConfigName::jump, VectorAssistant::VGet2D(0.f, 40.f), 0.1f, nullptr);
	move_input_handle_ = LoadGraph("data/ui/input/pad/button_xboxone_digital_analog_click_light_7.png");
	move_camera_input_handle_ = LoadGraph("data/ui/input/pad/button_xboxone_digital_analog_click_light_8.png");
}

InputControlUI::~InputControlUI()
{
	string_uis_.clear();
	button_uis_.clear();
	DeleteGraph(move_input_handle_);
	DeleteGraph(move_camera_input_handle_);
}

void InputControlUI::Awake()
{

}

void InputControlUI::Init()
{
	for (auto button_ui : button_uis_)
	{
		button_ui->Init();
	}
}

void InputControlUI::Update()
{
	for (auto button_ui : button_uis_)
	{
		button_ui->Update();
	}
	DrawSubScreen();
}

void InputControlUI::Draw()
{
	Draw2D::RotaGraph(screen_pos_, 1.f, 0.f, screen_->GetHandle(), TRUE);
}

void InputControlUI::DrawSubScreen()
{
	screen_->Up();
	for (auto string_ui : string_uis_)
	{
		string_ui->Draw();
	}

	for (auto button_ui : button_uis_)
	{
		button_ui->Draw();
	}
	const float kSize = 0.06f;
	const VECTOR kMoveInputPos = VectorAssistant::VGet2D(15.f, 50.f);
	Draw2D::RotaGraph(kMoveInputPos, kSize, 0.f, move_input_handle_, TRUE);
	const VECTOR kMoveCameraInputPos = VectorAssistant::VGet2D(90.f, 50.f);
	Draw2D::RotaGraph(kMoveCameraInputPos, kSize, 0.f, move_input_handle_, TRUE);
	screen_->Down();
}