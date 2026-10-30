#include<memory>
#include<string>
#include"DxLib.h"
#include"jump_string_ui.h"
#include<functional>
#include"draw_2D.h"

JumpStringUI::JumpStringUI()
	: StringUI("data/csv/ui/input_control/jump_ui.csv")
{

}

JumpStringUI::~JumpStringUI()
{

}

const void JumpStringUI::Draw() const
{
	Draw2D::ExtendStringToHandle(pos_, 1.f, 1.f, "ƒWƒƒƒ“ƒv", color_, font_handle_, edge_color_);
}