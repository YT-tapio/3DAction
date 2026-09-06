#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"lose_ui.h"
#include<string>
#include<functional>
#include"draw_2D.h"
#include"screen_size.h"
#include"vector_assistant.h"
#include"lerp.h"
#include"FPS.h"
#include"csv_file_assistant.h"
#include"font.h"
#include"button_ui.h"
#include"config_name.h"

LoseUI::LoseUI()
	: back_ground_pos_(VectorAssistant::VGet2D(float(kScreenWidth) * 0.5f, float(kScreenHeight) * 0.5f))
	, game_over_pos_(VectorAssistant::VGetZero())
	, offset_(VectorAssistant::VGet2D(50.f,-15.f))
	, retry_ui_pos_(VectorAssistant::VGet2D(300,600))
	, go_title_ui_pos_(VectorAssistant::VGet2D(1100, 600))
	, current_blend_num_(0.f)
	, target_blend_num_(180.f)
	, current_game_over_blend_num_(0.f)
	, current_button_blend_num_(0.f)
	, is_active_(FALSE)
{
	LoadFile();
	game_over_handle_ = LoadGraph("data/ui/game_over/game_over.png");
	auto button_size = 0.15f;
	retry_button_ = std::make_shared<ButtonUI>(ConfigName::retry, retry_ui_pos_, button_size, nullptr);
	go_title_button_ = std::make_shared<ButtonUI>(ConfigName::go_title, go_title_ui_pos_, button_size, nullptr);
	
	if (game_over_handle_ == -1) { printfDx("データ読み込み失敗\n"); }
	if (Abutton_image_handle_ == -1) { printfDx("データ読み込み失敗\n"); }
	if (Bbutton_image_handle_ == -1) { printfDx("データ読み込み失敗\n"); }

	font_handle_ = Font::CreateHandleOfFile("data/csv/font/result_font_data.csv");
	
	body_color_ = GetColor(255, 255, 255);
	edge_color_ = GetColor(0, 0, 0);
}

LoseUI::~LoseUI()
{
	DeleteGraph(game_over_handle_);
	DeleteFontToHandle(font_handle_);
}

void LoseUI::Init()
{
	retry_button_->Init();
	go_title_button_->Init();
}

void LoseUI::Update()
{
	if (!is_active_) { return; }
	float blend_speed = 5.f * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS();
	
	current_blend_num_ = Lerp::Lerpf(current_blend_num_, target_blend_num_, blend_speed );
	float game_over_target_blend_num = 230.f;
	float game_over_blend_speed = 10.f * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS();
	current_game_over_blend_num_ = Lerp::Lerpf(current_game_over_blend_num_, target_blend_num_, game_over_blend_speed);
	// 一致したらゲームオーバーの表示
	float diff = fabs(current_blend_num_ - target_blend_num_);
	if (diff > 0.f)
	{
		float up_speed = 5.f * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS();
		
		float game_over_blend_diff = fabs(current_game_over_blend_num_ - game_over_target_blend_num);
		game_over_pos_.y -= up_speed;
	}
	retry_button_->Update();
	go_title_button_->Update();

}

void LoseUI::Draw()
{
	if (!is_active_) { return; }
	DrawBackGround();
	DrawGameOver();
	DrawButton();
	retry_button_->Draw();
	go_title_button_->Draw();
}

void LoseUI::OnPlayerDeath()
{
	is_active_ = TRUE;
}

void LoseUI::LoadFile()
{

}

void LoseUI::DrawBackGround()
{
	auto draw_box = [this]() -> void
		{
			Draw2D::Box(back_ground_pos_, kScreenWidth, kScreenHeight, GetColor(0, 0, 0), TRUE);
		};

	Draw2D::Blend(draw_box, current_blend_num_);
}

void LoseUI::DrawGameOver()
{
	auto draw_game_over = [this]() -> void
		{
			Draw2D::RotaGraph(VAdd(back_ground_pos_, game_over_pos_), 0.75f, 0.f, game_over_handle_, TRUE);
		};

	Draw2D::Blend(draw_game_over, current_game_over_blend_num_);
}

void LoseUI::DrawButton()
{
	auto draw_button = [this]() -> void
		{
			Draw2D::RotaGraph(retry_ui_pos_, 0.25f, 0.f, Abutton_image_handle_, TRUE);
			Draw2D::StringToHandle(VAdd(retry_ui_pos_, offset_), "リトライ", body_color_, font_handle_, edge_color_);
			Draw2D::RotaGraph(go_title_ui_pos_, 0.25f, 0.f, Bbutton_image_handle_, TRUE);
			Draw2D::StringToHandle(VAdd(go_title_ui_pos_, offset_), "タイトルへ", body_color_, font_handle_, edge_color_);
		};

	Draw2D::Blend(draw_button, 255);
}