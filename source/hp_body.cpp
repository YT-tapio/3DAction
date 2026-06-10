#include<string>
#include<functional>
#include<memory>
#include"DxLib.h"
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"hp_body.h"
#include"vector_assistant.h"
#include"sub_screen.h"
#include"color.h"

HPBody::HPBody(const ImageData& data, const VECTOR& pos, float size_rate, float rot, std::function<int()> get_base_hp, std::function<int()> get_current_hp)
	: Object2D(data, pos, size_rate, rot)
	, get_base_hp_(get_base_hp)
	, get_current_hp_(get_current_hp)
	, blind_width_(0.f)
	, blind_height_(0.f)
	, blind_box_pos_(VectorAssistant::VGetZero())
{
	screen_ = std::make_shared<SubScreen>(1920, 1080);
}

HPBody::~HPBody()
{

}

void HPBody::Init()
{

}

void HPBody::Update()
{
	// 描画されているsize
	const auto kDispWidth = data_.width * size_rate_;
	const auto kDispHeight= data_.height * size_rate_;
	blind_height_ = kDispHeight;

	// TODO：減った時のlerpをする

	if (get_current_hp_() > 0)
	{
		auto ratio = 1 - float(get_current_hp_()) / get_base_hp_();
		blind_width_ = kDispWidth * ratio;
		// blind_height_ = kDispHeight * ratio;
	}
	else
	{
		blind_width_ = 0.f;
		// blind_height_ = 0.f;
	}
	blind_box_pos_ = VectorAssistant::VGet2D(pos_.x + (kDispWidth * 0.5f), pos_.y - (kDispHeight * 0.5f));
	//この中でscreenを立ち上げて描画
	SetUpScreen();
}

void HPBody::Draw()
{

	DrawFormatString(700, 400, GetColor(0, 0, 0), "%d", get_base_hp_());
	DrawFormatString(800, 400, GetColor(0, 0, 0), "%d", get_current_hp_());

	// 透過
	GraphFilter(screen_->GetHandle(), DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 10, TRUE, GetColor(0, 255, 0), 0);
	// 表示
	DrawGraph(0, 0, screen_->GetHandle(), TRUE);
}

void HPBody::Debug()
{

}

void HPBody::SetUpScreen()
{
	screen_->Up();
	// boxとhpバーを描画

	// hpバー
	DrawRotaGraph(static_cast<int>(pos_.x),
	static_cast<int>(pos_.y), size_rate_, rot_.z, handle_, TRUE, FALSE);
	
	DrawBox(static_cast<int>(blind_box_pos_.x), static_cast<int>(blind_box_pos_.y),
		static_cast<int>(blind_box_pos_.x - blind_width_), static_cast<int>(blind_box_pos_.y + blind_height_),Color::kBlack,TRUE);

	screen_->Down();
}