#include<string>
#include<memory>
#include"DxLib.h"
#include"move_string_ui.h"
#include<functional>
#include"draw_2d.h"

MoveStringUI::MoveStringUI()
	: StringUI("data/csv/ui/input_control/move_ui.csv")
{

}

MoveStringUI::~MoveStringUI()
{

}

const void MoveStringUI::Draw() const
{
	Draw2D::ExtendStringToHandle(pos_, 1.f, 1.f, "ˆÚ“®", color_, font_handle_, edge_color_);
}