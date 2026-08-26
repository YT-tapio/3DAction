#include<string>
#include<functional>
#include"DxLib.h"
#include"button_ui.h"
#include"lerp.h"
#include"FPS.h"
#include"draw_2D.h"
#include"button_ui_datas.h"

ButtonUI::ButtonUI(const std::string& name,std::function<void()> execute)
	: name_(name)
	, execute_(execute)
	, current_size_(1.f)
	, target_size_(1.f)
	, is_execute_(FALSE)
{

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
		
		// 処理を走らせる
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
	int handle = ButtonUIDatas::GetInstance().GetHandle(name_);
	Draw2D::RotaGraph(pos_, current_size_, 0.f, handle, TRUE);
}

bool ButtonUI::CheckMyButton()
{


	return FALSE;
}