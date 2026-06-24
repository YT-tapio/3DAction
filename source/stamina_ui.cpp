#include<memory>
#include<functional>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"ui_interface.h"
#include"stamina_ui.h"
#include"sub_screen.h"
#include"color.h"
#include<string>
#include"draw_2D.h"
#include"vector_assistant.h"
#include"condition_timer.h"
#include"lerp.h"
#include"FPS.h"
#include"csv_file_assistant.h"

StaminaUI::StaminaUI(std::function<float()> get_base_stamina, std::function<float()> get_current_stamina,
	std::function<bool()> can_use_stamina)
	: get_base_stamina_(get_base_stamina)
	, get_current_stamina_(get_current_stamina)
	, can_use_stamina_func_(can_use_stamina)
	, base_center_pos_(VectorAssistant::VGetZero())
	, base_scale_(0.f)
	, current_blend_value_(0.f)
	, target_blend_value_(0.f)
	, base_blend_speed_(0.f)
	, body_color_(0)
	, body_base_color_(0)
	, body_ratio_(0.f)
	, body_radius_(-1.f)
	, low_stamina_color_(0)
	, low_stamina_current_blend_value_(0.f)
	, low_stamina_target_blend_value_(0.f)
	, low_stamina_blend_speed_(0.f)
	, low_stamina_ratio_(0.f)
	, background_color_(0)
	, background_radius_(-1.f)
	, background_blend_value_(-1)
	, edge_color_(0)
	, edge_radius_(-1.f)
	, edge_thickness_(-1.f)
{
	// 画面を作る
	stamina_body_screen_ = std::make_shared<SubScreen>(110, 110);
	disp_timer_ = std::make_shared<ConditionTimer>(0.1f);

	LoadFile();

}

StaminaUI::~StaminaUI()
{

}

void StaminaUI::Init()
{

}

void StaminaUI::Update()
{
	StaminaBodyUpdate();

	// スタミナがmaxの際表示をやめる
	if (body_ratio_ == 1.f)
	{
		// タイマーを更新
		disp_timer_->Update();

		if(disp_timer_->GetIsEnd())
		{
			// だんだんと表示をやめる
			target_blend_value_ = 0.f;
		}
	}
	else
	{
		target_blend_value_ = 255.f;
		disp_timer_->ReStart();
	}

	if (current_blend_value_ != target_blend_value_)
	{
		current_blend_value_ = Lerp::Lerpf(current_blend_value_, target_blend_value_, FPS::GetInstance().GetDeltaTime() * 60.f * base_blend_speed_);
	}
	
}

const void StaminaUI::Draw() const
{
	if (current_blend_value_ == 0.f) { return; }

	Draw2D::Blend([this]() {UseBlendDraw(); }, current_blend_value_);
}

void StaminaUI::StaminaBodyUpdate()
{
	// スタミナの割合を決める
	body_ratio_ = (get_current_stamina_() / get_base_stamina_());
	
	// スタミナの量が低い時かつスタミナを使用できるとき
	if (body_ratio_ < low_stamina_ratio_ && can_use_stamina_func_())
	{
		if (low_stamina_current_blend_value_ == 180) { low_stamina_target_blend_value_ = 0.f; }
		if (low_stamina_current_blend_value_ == 0) { low_stamina_target_blend_value_ = 180; }
		low_stamina_current_blend_value_ = Lerp::Lerpf(low_stamina_current_blend_value_, low_stamina_target_blend_value_,
			low_stamina_blend_speed_ * FPS::GetInstance().GetDeltaTime() * 60.f);
	}
	else
	{
		low_stamina_target_blend_value_ = 0.f;
		low_stamina_current_blend_value_ = 0.f;
	}

	if (can_use_stamina_func_())
	{
		body_color_ = body_base_color_;
	}
	else
	{
		body_color_ = Color::kRed;
	}

	// screenに丸を描画
	stamina_body_screen_->Up();
	Draw2D::Circle(VectorAssistant::VGet2D(float(stamina_body_screen_->GetScreenWidth()) * 0.5f, 
		float(stamina_body_screen_->GetScreenHeight()) * 0.5f), body_radius_, body_color_, FALSE, body_thickness_);
	stamina_body_screen_->Down();
}

const void StaminaUI::UseBlendDraw() const
{
	Draw2D::Blend([this]() {Draw2D::Circle(base_center_pos_, background_radius_ * base_scale_, background_color_, TRUE); }, background_blend_value_);	// 背景の描画
	
	// 赤く点滅する円を描画
	Draw2D::Blend([this]() {Draw2D::Circle(base_center_pos_, body_radius_ * base_scale_, low_stamina_color_, FALSE, body_thickness_ * base_scale_); }, low_stamina_current_blend_value_);
	Draw2D::CircleGauge(base_center_pos_, body_ratio_, stamina_body_screen_->GetHandle(), 0.f, base_scale_);	// 本体の描画
	
	auto edge_thickness = edge_thickness_ * base_scale_;
	auto edge_radius = body_radius_ * base_scale_;
	Draw2D::Circle(base_center_pos_, edge_radius - (body_thickness_ * 0.5f + edge_thickness * 0.5f), edge_color_, FALSE, edge_thickness);
	Draw2D::Circle(base_center_pos_, edge_radius + (body_thickness_ * 0.5f + edge_thickness * 0.5f), edge_color_, FALSE, edge_thickness);
}

void StaminaUI::LoadFile()
{
	std::ifstream file("data/csv/ui/player/stamina/stamina_data.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の2行を飛ばす
	std::getline(file, line);
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう
	
		// 全てをまとめるもの
		base_center_pos_ = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		base_scale_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_blend_speed_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		
		// 本体
		body_color_ = CSVFileAssistant::GetColorOfCSVFile(ss, data);
		body_base_color_ = body_color_;
		body_radius_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		body_thickness_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		
		// hpが低い時に描画する丸
		low_stamina_color_ = CSVFileAssistant::GetColorOfCSVFile(ss, data);
		low_stamina_blend_speed_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		low_stamina_ratio_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);

		// 背景
		background_color_ = CSVFileAssistant::GetColorOfCSVFile(ss, data);
		background_blend_value_ = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		background_radius_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);

		// 枠
		edge_color_ = CSVFileAssistant::GetColorOfCSVFile(ss, data);
		edge_radius_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		edge_thickness_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
	}

}