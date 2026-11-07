#include<memory>
#include<string>
#include"DxLib.h"
#include"number_popup_ui.h"
#include"popup_ui.h"
#include"sub_screen.h"
#include"vector_assistant.h"
#include<functional>
#include"draw_2D.h"
#include"font_data.h"
#include"image_repository.h"

NumberPopupUI::NumberPopupUI(const int& color, const int& edge_color)
	: PopupUIHolderBase()
	, color_(color)
	, edge_color_(edge_color)
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

void NumberPopupUI::Spawn(const VECTOR& base_pos,const int& damage, const bool& is_critical)
{
	const float kSize = 75.f;
	// 画像を用意
	MakeHandle(damage,is_critical);
	popup_ui_->Spawn(base_pos, sub_screen_->GetHandle(),kSize);
	auto is_active = popup_ui_->GetIsActive();
}

void NumberPopupUI::MakeHandle(const int& damage, const bool& is_critical)
{
	sub_screen_->Up();
	// 文字の描画を行う
	VECTOR center_pos = sub_screen_->GetCenterPos();
	// fontの大きさとfontのサイズ
	int width = -1;
	int height = -1;
	int font_handle = FontData::GetInstance().GetHandle("popup_font");
	GetDrawFormatStringSizeToHandle(&width, &height, NULL, font_handle, "%d", static_cast<int>(damage));
	VECTOR start_pos = VSub(center_pos, VectorAssistant::VGet2D(width * 0.5f, height * 0.5f));
	Draw2D::FormatStringToHandle(start_pos, "%d", color_, font_handle, static_cast<int>(damage), edge_color_);
	if (is_critical)
	{
		DrawBillboard3D(start_pos, 0.5f, 0.5f, 10.f, 0.f, ImageRepository::GetInstance().GetHandle("critical_damage"), TRUE);
	}
	sub_screen_->Down();
}
