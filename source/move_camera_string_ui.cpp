#include<string>
#include<memory>
#include"DxLib.h"
#include"move_camera_string_ui.h"
#include<functional>
#include"draw_2d.h"

MoveCameraStringUI::MoveCameraStringUI()
	: StringUI("data/csv/ui/input_control/move_camera_ui.csv")
{

}

MoveCameraStringUI::~MoveCameraStringUI()
{

}

const void MoveCameraStringUI::Draw() const
{
	Draw2D::ExtendStringToHandle(pos_, 1.f, 1.f, "Ž‹“_ˆÚ“®", color_, font_handle_, edge_color_);
}