#include<string>
#include<memory>
#include"DxLib.h"
#include"avoid_string_ui.h"
#include<functional>
#include"draw_2D.h"

AvoidStringUI::AvoidStringUI()
	: StringUI("data/csv/ui/input_control/avoid_ui.csv")
{

}

AvoidStringUI::~AvoidStringUI()
{

}

const void AvoidStringUI::Draw() const
{
	Draw2D::ExtendStringToHandle(pos_, 1.f, 1.f, "’P‰Ÿ‚µF‰ñ”ğ", color_, font_handle_, edge_color_);
}