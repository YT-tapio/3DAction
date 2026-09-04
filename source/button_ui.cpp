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

ButtonUI::ButtonUI(const ConfigName& name, const VECTOR& pos,const float& default_size,std::function<void()> execute)
	: name_(name)
	, execute_(execute)
	, default_size_(default_size)
	, is_execute_(FALSE)
	, pos_(pos)
{
	target_size_ = default_size_;
	current_size_ = default_size_;
}

ButtonUI::~ButtonUI()
{
	
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
	Draw2D::RotaGraph(pos_, current_size_, 0.f, ButtonUIDatas::GetInstance().GetHandle(name), TRUE);
}

bool ButtonUI::CheckMyButton()
{	
	return InputManager::GetInstance().IsPushMainInput(name_);
}