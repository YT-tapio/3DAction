#include<memory>
#include<string>
#include"DxLib.h"
#include"number_popup_ui.h"
#include"popup_ui.h"
#include"sub_screen.h"
#include"vector_assistant.h"
#include<functional>
#include"draw_2D.h"

NumberPopupUI::NumberPopupUI()
{
	popup_ui_ = std::make_shared<PopupUI>();
	sub_screen_ = std::make_shared<SubScreen>();
}

NumberPopupUI::~NumberPopupUI()
{

}

void NumberPopupUI::Init()
{
	popup_ui_->Init();
	sub_screen_->Init();
}

void NumberPopupUI::Update()
{
	popup_ui_->Update();
}

void NumberPopupUI::Draw()
{
	popup_ui_->Draw();
}

void NumberPopupUI::Spawn(const VECTOR& base_pos,const int& damage)
{
	// 画像を用意
	MakeHandle(damage);
	popup_ui_->Spawn(base_pos, sub_screen_->GetHandle());
}

void NumberPopupUI::MakeHandle(const int& damage)
{
	sub_screen_->Up();
	// 文字の描画を行う
	VECTOR center_pos = sub_screen_->GetCenterPos();

	// fontの大きさとfontのサイズ
	int width = -1;
	int height = -1;
	GetDrawFormatStringSizeToHandle(&width, &height, NULL, font_handle_, "%d", static_cast<int>(damage));
	VECTOR start_pos = VSub(center_pos, VectorAssistant::VGet2D(width * 0.5f, height * 0.5f));
	Draw2D::FormatStringToHandle(start_pos, "%d", color_, font_handle_, static_cast<int>(damage), edge_color_);
	sub_screen_->Down();
}
