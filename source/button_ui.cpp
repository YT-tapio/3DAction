#include<string>
#include<functional>
#include"DxLib.h"
#include"button_ui.h"
#include"lerp.h"
#include"FPS.h"
#include"draw_2D.h"
#include"button_ui_datas.h"
#include<memory>
#include<unordered_map>
#include"input_manager.h"
#include"input_base.h"
#include"config_datas.h"
#include"config_data.h"

ButtonUI::ButtonUI(const ConfigName& name,std::function<void()> execute)
	: name_(name)
	, execute_(execute)
	, target_size_(0.1f)
	, default_size_(0.1f)
	, is_execute_(FALSE)
	, pos_(VectorAssistant::VGet2D(100.f,100.f))
{
	current_size_ = default_size_;
	
}

ButtonUI::~ButtonUI()
{
	DeleteGraph(handle_);
}

void ButtonUI::Init()
{

}

void ButtonUI::Update()
{
	// ボタンが押されているかによってサイズの変更
	if (CheckMyButton())
	{
		target_size_ = default_size_ * 0.8f;
		
		// 処理を実行
		if (execute_ != nullptr && !is_execute_)
		{
			execute_();
			is_execute_ = TRUE;
		}
	}
	else
	{
		target_size_ = default_size_;
	}
	current_size_ = Lerp::Dampf(current_size_, target_size_, FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS());
}

void ButtonUI::Draw()
{
	auto name = ConfigDatas::GetInstance().GetConfigData(name_).pad.name;
	int handle = ButtonUIDatas::GetInstance().GetHandle(name);
	Draw2D::RotaGraph(pos_, current_size_, 0.f, handle, TRUE);
}

bool ButtonUI::CheckMyButton()
{	
	return InputManager::GetInstance().IsPushMainInput(name_);
}