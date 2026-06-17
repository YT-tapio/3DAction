#include<string>
#include<functional>
#include<memory>
#include<vector>
#include"DxLib.h"
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"hp_body.h"
#include"vector_assistant.h"
#include"sub_screen.h"
#include"color.h"
#include"lerp.h"
#include"draw_2D.h"
#include"FPS.h"

HPBody::HPBody(const ImageData& data, const VECTOR& pos, float size_rate, float rot, std::function<int()> get_base_hp, std::function<int()> get_current_hp)
	: Object2D(data, pos, size_rate, rot)
	, get_base_hp_(get_base_hp)
	, get_current_hp_(get_current_hp)
	, blind_width_(0.f)
	, blind_height_(0.f)
	, blind_box_pos_(VectorAssistant::VGetZero())
	, now_ratio_(0.f)
	, flash_value_(0.f)
	, target_flash_value_(100.f)
	, flash_up_(TRUE)
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
	if (now_ratio_ == 1.f) { return; }
	// ï`âÊÇ≥ÇÍÇƒÇ¢ÇÈsize
	const auto kDispWidth = data_.width * size_rate_;
	const auto kDispHeight= data_.height * size_rate_;
	blind_height_ = kDispHeight;
	
	auto target_hp = get_current_hp_();
	
	auto target_ratio = 1 - float(target_hp) / get_base_hp_();
	// ï‚äÆ
	now_ratio_ = Lerp::Dampf(now_ratio_, target_ratio, 0.1f);
	blind_width_ = kDispWidth * now_ratio_;

	blind_box_pos_ = VectorAssistant::VGet2D(pos_.x + (kDispWidth * 0.5f), pos_.y - (kDispHeight * 0.5f));
	// ratioÇ™àÍíËà»è„Ç…Ç»ÇÈÇ∆ì¡ï èàóù
	if (now_ratio_ >= 0.65f)
	{
		if (flash_value_ >= kMaxFlashValue) { target_flash_value_ = kMinFlashValue; }
		if (flash_value_ <= kMinFlashValue) { target_flash_value_ = kMaxFlashValue; }
		flash_value_ = Lerp::Lerpf(flash_value_, target_flash_value_, kFlashSpeed * FPS::GetInstance().GetDeltaTime() * 60.f);
	}

	// Ç±ÇÃíÜÇ≈screenÇóßÇøè„Ç∞Çƒï`âÊ
	SetUpScreen();
}

void HPBody::Draw()
{	
	// ìßâﬂ
	GraphFilter(screen_->GetHandle(), DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 10, TRUE, GetColor(0, 255, 0), 0);
	GraphFilter(screen_->GetHandle(), DX_GRAPH_FILTER_HSB, 0, static_cast<int>(flash_value_), 0, 2);
	// ï\é¶
	DrawGraph(0, 0, screen_->GetHandle(), TRUE);
}

void HPBody::Debug()
{

}

void HPBody::SetUpScreen()
{
	screen_->Up();
	// boxÇ∆hpÉoÅ[Çï`âÊ

	// hpÉoÅ[
	DrawRotaGraph(static_cast<int>(pos_.x),
	static_cast<int>(pos_.y), size_rate_, rot_.z, handle_, TRUE, FALSE);
	
	DrawBox(static_cast<int>(blind_box_pos_.x), static_cast<int>(blind_box_pos_.y),
		static_cast<int>(blind_box_pos_.x - blind_width_), static_cast<int>(blind_box_pos_.y + blind_height_),Color::kBlack,TRUE);

	screen_->Down();
}