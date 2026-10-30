#include<string>
#include<memory>
#include"DxLib.h"
#include"dash_string_ui.h"
#include<functional>
#include"draw_2d.h"

DashStringUI::DashStringUI()
	: StringUI("data/csv/ui/input_control/dash_ui.csv")
{

}

DashStringUI::~DashStringUI()
{

}

const void DashStringUI::Draw() const
{
	Draw2D::ExtendStringToHandle(pos_, 1.f, 1.f, "長押し：ダッシュ", color_, font_handle_, edge_color_);
}