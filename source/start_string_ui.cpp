#include<string>
#include"DxLib.h"
#include"start_string_ui.h"
#include<functional>
#include"draw_2D.h"

StartStringUI::StartStringUI()
	: StringUI("data/csv/ui/title/start_ui.csv")
{

}

StartStringUI::~StartStringUI()
{

}

const void StartStringUI::Draw() const
{
	Draw2D::ExtendStringToHandle(pos_, 1.f, 1.f, "ボタンでゲームスタート", color_, font_handle_, edge_color_);
}