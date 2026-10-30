#include<string>
#include<memory>
#include"DxLib.h"
#include"target_string_ui.h"
#include<functional>
#include"draw_2D.h"

TargetStringUI::TargetStringUI()
	: StringUI("data/csv/ui/input_control/lock_on_ui.csv")
{

}

TargetStringUI::~TargetStringUI()
{

}

const void TargetStringUI::Draw() const
{
	Draw2D::ExtendStringToHandle(pos_, 1.f, 1.f, "ÉçÉbÉNÉIÉì", color_, font_handle_, edge_color_);
}