#include<string>
#include<fstream>
#include<sstream>
#include<memory>
#include<functional>
#include"DxLib.h"
#include"won_ui.h"
#include"draw_2d.h"
#include"vector_assistant.h"
#include"condition_timer.h"
#include"csv_file_assistant.h"
#include"lerp.h"
#include"fps.h"
#include"font.h"
#include"sound_manager.h"
#include"button_ui.h"
#include"config_name.h"

WonUI::WonUI()
	: base_pos_(VectorAssistant::VGetZero())
	, back_ground_size_(VectorAssistant::VGetZero())
	, retry_ui_pos_(VectorAssistant::VGet2D(830.f,800.f))
	, go_title_ui_pos_(VectorAssistant::VGet2D(1180.f,800.f))
	, offset_(VGet(440,-100.f,0.f))
	, offset_button_pos_(VectorAssistant::VGet2D(50.f,-20.f))
	, base_size_(1.f)
	, just_avoid_num_(0)
	, avoid_collect_num_(0)
	, enemy_take_most_damage_(0.f)
	, target_back_ground_blend_num_(0.f)
	, current_back_ground_blend_num_(0.f)
	, is_active_(FALSE)
	, is_play_(FALSE)
{
	LoadFile();
	
	retry_button_ = std::make_shared<ButtonUI>(ConfigName::retry, retry_ui_pos_, 0.15f, nullptr);
	go_title_button_ = std::make_shared<ButtonUI>(ConfigName::go_title, go_title_ui_pos_, 0.15f, nullptr);
	go_next_scene_font_.handle = Font::CreateHandleOfFile("data/csv/font/game_to_next_scene_font_data.csv");
	go_next_scene_font_.body_color = GetColor(255, 255, 255);
	go_next_scene_font_.body_color = GetColor(0, 0, 0);
	timer_ = std::make_shared<ConditionTimer>(3.4f);
	timer_->Init();
}

WonUI::~WonUI()
{
	DeleteFontToHandle(go_next_scene_font_.handle);
}

void WonUI::Init()
{
	is_active_ = FALSE;
	avoid_collect_num_ = 0;
}

void WonUI::Update()
{
	if (!is_active_) { return; }
	timer_->Update();
	if (!timer_->GetIsEnd()) { return; }
	current_back_ground_blend_num_ = Lerp::Lerpf(current_back_ground_blend_num_, target_back_ground_blend_num_, back_ground_blend_speed_ * FPS::GetInstance().GetDeltaTime()* FPS::GetInstance().GetTargetFPS());
	if (!is_play_)
	{
		SoundManager::GetInstance().Play2DSound("clear");
		is_play_ = TRUE;
	}
	retry_button_->Update();
	go_title_button_->Update();
}

void WonUI::Draw()
{
	if (!timer_->GetIsEnd()) { return; }
	DrawBackGround();
	DrawWonImage();
	DrawAvoidCollectNum();
	DrawMostTakeDamageEnemy();
	DrawGameToNext();
}

void WonUI::OnTakeDamage(const float& damage)
{
	if (damage > enemy_take_most_damage_) { enemy_take_most_damage_ = damage; }
}

void WonUI::OnEnemyDeath()
{
	// ここでタイマーの起動を行う描画させる
	is_active_ = TRUE;
	timer_->ReStart();
}

void WonUI::OnPlayerJustAvoid()
{
	just_avoid_num_++;
}

void WonUI::OnPlayerAvoidCollect()
{
	avoid_collect_num_++;
}

void WonUI::LoadFile()
{
	std::ifstream file("data/csv/ui/won/won_ui_data.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}
	std::string won_image_file_path;
	std::string avoid_collect_font_path;
	std::string most_take_damage_font_path;
	// 最初の行を飛ばす
	std::getline(file, line);
	std::getline(file, line);
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;

		base_pos_ = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		base_size_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		back_ground_size_ = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		target_back_ground_blend_num_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		back_ground_blend_speed_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		
		// 勝利の文字
		won_image_pos_ = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		won_image_file_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		won_image_size_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		won_image_rot_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);

		// 回避
		avoid_collect_pos_ = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		avoid_collect_font_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		avoid_collect_font_.body_color = CSVFileAssistant::GetColorOfCSVFile(ss, data);
		avoid_collect_font_.edge_color = CSVFileAssistant::GetColorOfCSVFile(ss, data);
		// ダメージ
		most_damage_pos_ = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		most_take_damage_font_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		most_damage_font_.body_color = CSVFileAssistant::GetColorOfCSVFile(ss, data);
		most_damage_font_.edge_color = CSVFileAssistant::GetColorOfCSVFile(ss, data);
	}
	won_image_handle_ = LoadGraph(won_image_file_path.c_str());
	avoid_collect_font_.handle = Font::CreateHandleOfFile(avoid_collect_font_path);
	most_damage_font_.handle = Font::CreateHandleOfFile(most_take_damage_font_path);

}

void WonUI::DrawBackGround()
{
	auto draw_box = [this]()
		{
			Draw2D::Box(base_pos_, static_cast<int>(back_ground_size_.x), static_cast<int>(back_ground_size_.y), GetColor(0, 0, 1), TRUE);
		};
	Draw2D::Blend(draw_box, 100);
}

void WonUI::DrawWonImage()
{
	Draw2D::RotaGraph(VAdd(base_pos_,won_image_pos_), won_image_size_, won_image_rot_, won_image_handle_, TRUE);
}

void WonUI::DrawAvoidCollectNum()
{
	Draw2D::StringToHandle(VAdd(base_pos_, avoid_collect_pos_), "回避成功数", avoid_collect_font_.body_color, avoid_collect_font_.handle,avoid_collect_font_.edge_color);
	auto offset_num_pos = VAdd(VAdd(base_pos_, avoid_collect_pos_), offset_);
	Draw2D::ExtendFormatStringToHandleEdge(offset_num_pos, 3.f, 3.f, "%d", avoid_collect_font_.body_color, avoid_collect_font_.edge_color, avoid_collect_font_.handle, avoid_collect_num_);
}

void WonUI::DrawMostTakeDamageEnemy()
{
	Draw2D::StringToHandle(VAdd(base_pos_, most_damage_pos_), "最大ダメージ", most_damage_font_.body_color, most_damage_font_.handle, most_damage_font_.edge_color);
	//Draw2D::StringToHandle(VAdd(VAdd(base_pos_, most_damage_pos_), offset_), "最大ダメージ", most_damage_font_.body_color, most_damage_font_.handle, most_damage_font_.edge_color);
	
	auto offset_num_pos = VAdd(VAdd(base_pos_, most_damage_pos_), offset_);

	Draw2D::ExtendFormatStringToHandleEdge(offset_num_pos, 3.f, 3.f, "%d", most_damage_font_.body_color, most_damage_font_.edge_color, most_damage_font_.handle, static_cast<int>(enemy_take_most_damage_));
	//Draw2D::FormatStringToHandle(VAdd(VAdd(base_pos_, most_damage_pos_), offset_), "%d", most_damage_font_.body_color, most_damage_font_.handle, static_cast<int>(enemy_take_most_damage_), most_damage_font_.edge_color);
}

void WonUI::DrawGameToNext()
{
	retry_button_->Draw();
	Draw2D::StringToHandle(VAdd(retry_ui_pos_, offset_button_pos_), "もう一度", go_next_scene_font_.body_color, go_next_scene_font_.handle, go_next_scene_font_.edge_color);
	go_title_button_->Draw();
	Draw2D::StringToHandle(VAdd(go_title_ui_pos_, offset_button_pos_), "タイトルへ", go_next_scene_font_.body_color, go_next_scene_font_.handle, go_next_scene_font_.edge_color);
}