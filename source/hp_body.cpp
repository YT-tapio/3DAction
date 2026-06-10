#include<string>
#include<functional>
#include"DxLib.h"
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"hp_body.h"
#include"vector_assistant.h"

HPBody::HPBody(const ImageData& data, const VECTOR& pos, float size_rate, float rot, std::function<int()> get_base_hp, std::function<int()> get_current_hp)
	: Object2D(data,pos,size_rate,rot)
	, get_base_hp_(get_base_hp)
	, get_current_hp_(get_current_hp)
	, blind_width_(0.f)
	, blind_height_(0.f)
{

}

HPBody::~HPBody()
{

}

void HPBody::Init()
{

}

void HPBody::Update()
{
	// •`‰æ‚³‚ê‚Ä‚¢‚ésize
	const auto kDispWidth = data_.width * size_rate_;
	const auto kDispHeight= data_.height * size_rate_;
	blind_height_ = kDispHeight;
	if (get_current_hp_() > 0)
	{
		auto ratio = float(get_current_hp_()) / get_base_hp_();
		blind_width_ = kDispWidth * ratio;
		// blind_height_ = kDispHeight * ratio;
	}
	else
	{
		blind_width_ = 0.f;
		// blind_height_ = 0.f;
	}
	
}

void HPBody::Draw()
{
	DrawFormatString(700, 400, GetColor(0, 0, 0), "%d", get_base_hp_());
	DrawFormatString(800, 400, GetColor(0, 0, 0), "%d", get_current_hp_());
	
	// ‚±‚±‚Ébox‚ð•\Ž¦‚³‚¹‚Ä“§‰ß‚·‚é
	Object2D::Draw();
	DrawBox(static_cast<int>(pos_.x - blind_width_), static_cast<int>(pos_.y - (blind_height_ * 0.5f)),
		static_cast<int>(pos_.x + blind_width_ ), static_cast<int>(pos_.y + (blind_height_*0.5f)), GetColor(255, 255, 255), TRUE);
}

void HPBody::Debug()
{

}