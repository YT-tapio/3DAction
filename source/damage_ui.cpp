#include<memory>
#include<string>
#include"DxLib.h"
#include"string_ui.h"
#include"damage_ui.h"
#include"vector_assistant.h"
#include"condition_timer.h"
#include"lerp.h"
#include<functional>
#include"draw_2d.h"
#include"random.h"
#include"time.h"
#include"sub_screen.h"
#include<sstream>
#include<fstream>
#include<windows.h>
#include"csv_file_assistant.h"
#include"font.h"

DamageUI::DamageUI(const std::string& file_path)
	: stop_timer_(std::make_shared<ConditionTimer>(2.f))
	, time_(std::make_shared<Time>())
	, pos_(VectorAssistant::VGetZero())
	, spawn_pos_(VectorAssistant::VGetZero())
	, font_handle_(-1)
	, font_color_(-1)
	, edge_color_(-1)
	, default_up_speed_(1.f)
	, current_up_speed_(0.f)
	, out_up_speed_(0.4f)
	, damage_(0.f)
	, alpha_value_(255.f)
	, is_jump_(FALSE)
	, is_active_(FALSE)
{
	LoadFile(file_path);
	damage_screen_ = std::make_shared<SubScreen>(400, 400);
}

DamageUI::~DamageUI()
{
	// フォントデータの開放
	DeleteFontToHandle(font_handle_);
}

void DamageUI::Init()
{
	pos_ = VectorAssistant::VGetZero();
	spawn_pos_ = VectorAssistant::VGetZero();
	current_up_speed_ = 0.f;
	damage_ = 0.f;
	is_jump_ = TRUE;
	is_active_ = FALSE;
	stop_timer_->Init();
}

void DamageUI::Update()
{
	if(alpha_value_ < 0.1f)
	{
		is_active_ = FALSE;
	}
	time_->Update();
	// スポーンしてからジャンプさせる
	if (is_jump_)
	{
		current_up_speed_ -= 0.5f*time_->GetFPSRate();
		pos_.y += current_up_speed_;

		if (spawn_pos_.y > pos_.y)
		{
			spawn_pos_.y = pos_.y;
			is_jump_ = FALSE;
		}
	}
	else
	{
		// 
		if (!stop_timer_->GetIsEnd()) { stop_timer_->Update(); }
		if (stop_timer_->GetIsEnd())
		{
			// だんだんと消えるかつ上昇していく
			alpha_value_ = Lerp::Dampf(alpha_value_, 0.f, 0.5f * time_->GetFPSRate());
			pos_.y += out_up_speed_ * time_->GetFPSRate();
		}
	}
	
}

const void DamageUI::Draw() const
{
	if (alpha_value_ == 0.f) 
	{ 
		return;
	}

	// 描画する
	auto function = [this]() -> void
		{
			DrawBillboard3D(pos_, 0.5f, 0.5f, 10.f, 0.f, damage_screen_->GetHandle(), TRUE);
		};

	Draw2D::Blend(function, alpha_value_);

}

void DamageUI::Spawn(const VECTOR& pos, const float& damage)
{
	// 引数の座標を基準にランダムな場所にスポーンさせる
	spawn_pos_ = RandomSpawnPos(pos);
	pos_ = spawn_pos_;
	damage_ = damage;
	current_up_speed_ = default_up_speed_;
	alpha_value_ = 255.f;
	is_jump_ = TRUE;
	is_active_ = TRUE;
	stop_timer_->ReStart();

	// この際に描画して画像を作る
	DrawDamage();
}

const bool DamageUI::GetIsActive() const
{
	return is_active_;
}

VECTOR DamageUI::RandomSpawnPos(const VECTOR& pos)
{
	VECTOR random_pos = VectorAssistant::VGetZero();
	int random_width = GetUniformRandom(-10, 10);
	int random_height = -GetUniformRandom(-3, 0);
	random_pos = VAdd(pos, VectorAssistant::VGet2D(random_width, random_height));
	// printfDx("x：%.2f,y：%.2f\n", random_pos.x, random_pos.y);
	return random_pos;
}

void DamageUI::DrawDamage()
{
	VECTOR center_pos = damage_screen_->GetCenterPos();
	
	// fontの大きさとfontのサイズ
	int width = -1;
	int height = -1;
	GetDrawFormatStringSizeToHandle(&width, &height, NULL, font_handle_, "%d", static_cast<int>(damage_));
	VECTOR start_pos = VSub(center_pos, VectorAssistant::VGet2D(width * 0.5f, height * 0.5f));
	// 描画
	damage_screen_->Up();
	// SetFontEdgeSize(10);
	Draw2D::FormatStringToHandle(start_pos, "%d", font_color_, font_handle_, static_cast<int>(damage_), edge_color_);
	damage_screen_->Down();
}

void DamageUI::LoadFile(const std::string& path)
{
	// 
	std::ifstream file(path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
	}

	// 2行を飛ばす
	std::getline(file, line);
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		// 
		auto font_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		font_handle_ = Font::CreateHandleOfFile(font_path);
		//font_handle_ = -1;
		font_color_ = CSVFileAssistant::GetColorOfCSVFile(ss,data);
		edge_color_ = CSVFileAssistant::GetColorOfCSVFile(ss, data);
	}

}