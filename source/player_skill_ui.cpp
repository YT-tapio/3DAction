#include<sstream>
#include<fstream>
#include<string>
#include<functional>
#include"DxLib.h"
#include"player_skill_ui.h"
#include"vector_assistant.h"
#include"csv_file_assistant.h"
#include"draw_2d.h"
#include"sub_screen.h"
#include"lerp.h"
#include"time.h"
#include"button_ui.h"

PlayerSkillUI::PlayerSkillUI(const VECTOR& pos, const int font_handle, const int body_color, const int edge_color,const ConfigName& name)
	: pos_(pos)
	, offset_button_pos_(VectorAssistant::VGet2D(-50.f,18.f))
	, cool_time_ratio_(nullptr)
	, can_use_(nullptr)
	, font_handle_(font_handle)
	, body_color_(body_color)
	, edge_color_(edge_color)
	, current_alpha_value_(0.f)
	, target_alpha_value_(0.f)
	, dark_percent_(0.f)
{
	time_ = std::make_shared<Time>();
	button_ = std::make_shared<ButtonUI>(name, VAdd(pos_, offset_button_pos_),0.07f, nullptr);

	// 丸が描画された画像を作る
	MakeCircleHandle();

	
}

PlayerSkillUI::~PlayerSkillUI()
{

}

void PlayerSkillUI::Init()
{

}

void PlayerSkillUI::Update()
{
	time_->Update();
	button_->Update();
	// 暗くする

	// スキルが使えるとき
	if (can_use_())
	{
		target_alpha_value_ = 0.f;
		dark_percent_ = 0.f;
	}
	else
	{
		target_alpha_value_ = 255.f;
		dark_percent_ = 0.5f;
	}
	// ラープ処理
	current_alpha_value_ = Lerp::Dampf(current_alpha_value_, target_alpha_value_, kBlendSpeed * time_->GetFPSRate());

}

void PlayerSkillUI::Draw()
{
	// 暗くなるものを描画
	auto draw_icon = [this]() -> void {DrawDarkUI(); };
	Draw2D::Dark(draw_icon, dark_percent_);

	auto draw_cool_time_gauge = [this]() -> void {Draw2D::CircleGauge(pos_, cool_time_ratio_(), sub_screen_->GetHandle()); };
	Draw2D::Blend(draw_cool_time_gauge, current_alpha_value_);
}

void PlayerSkillUI::SetSkill(const SkillUIData& skill_data, std::function<float()> cool_time_ratio, std::function<bool()> can_use)
{
	// データの入れ替え
	data_ = skill_data;
	cool_time_ratio_ = cool_time_ratio;
	can_use_ = can_use;
}

void PlayerSkillUI::LoadFile()
{
	// スキルid
	std::ifstream file("data/csv/ui/skill/.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
	}

	// 最初の行を飛ばす
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;

		
	}

}

void PlayerSkillUI::MakeCircleHandle()
{
	sub_screen_ = std::make_shared<SubScreen>(100, 100);

	sub_screen_->Up();
	Draw2D::Circle(sub_screen_->GetCenterPos(), 33.f, GetColor(124, 255, 90), FALSE,3.f);
	sub_screen_->Down();
}

void PlayerSkillUI::DrawDarkUI()
{
	// 操作アイコンの表示
	button_->Draw();

	auto draw_back_ground = [this]() -> void { Draw2D::Circle(pos_, 33.f, GetColor(101, 110, 128), TRUE); };
	Draw2D::Blend(draw_back_ground, 100);
	// アイコンの表示
	Draw2D::RotaGraph(pos_, 1.f, 0.f, data_.icon_handle, TRUE);
	
	int icon_width = -1;
	int icon_height = -1;
	GetGraphSize(data_.icon_handle, &icon_width, &icon_height);
	VECTOR name_pos = VAdd(pos_, VGet(icon_width, 0.f, 0.f));
	// スキル名描画
	Draw2D::FormatStringToHandle(name_pos, "%s", body_color_, font_handle_, data_.name.c_str(), edge_color_);
}