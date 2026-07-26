#include<sstream>
#include<fstream>
#include<string>
#include<functional>
#include"DxLib.h"
#include"player_skill_ui.h"
#include"csv_file_assistant.h"
#include"draw_2d.h"
#include"sub_screen.h"
#include"lerp.h"

PlayerSkillUI::PlayerSkillUI(const VECTOR& pos, const int& pad_handle,const int font_handle,const int body_color,const int edge_color)
	: pos_(pos)
	, cool_time_ratio_(nullptr)
	, can_use_(nullptr)
	, input_handle_(pad_handle)
	, font_handle_(font_handle)
	, body_color_(body_color)
	, edge_color_(edge_color)
	, current_alpha_value_(0.f)
	, target_alpha_value_(0.f)
{
	//LoadFile();

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
	// クールタイムの割合を取得し円をへらす

	// ここで消える処理をする
	
	// canuseがFALSEの場合は消える
	if (can_use_())
	{
		target_alpha_value_ = 0.f;
	}
	else
	{
		target_alpha_value_ = 255.f;
	}
	current_alpha_value_ = Lerp::Dampf(current_alpha_value_, target_alpha_value_, 0.3f);

}

void PlayerSkillUI::Draw()
{
	// 自分に対応している操作ボタンの描画

	// アイコンなどの描画
	Draw2D::RotaGraph(VAdd(pos_,VGet(-50.f,18.f,0.f)), 0.07f, 0.f, input_handle_, TRUE);
	Draw2D::RotaGraph(pos_, 1.f, 0.f, data_.icon_handle, TRUE);
	int icon_width = -1;
	int icon_height = -1;
	GetGraphSize(data_.icon_handle, &icon_width, &icon_height);
	VECTOR name_pos = VAdd(pos_, VGet(icon_width, 0.f, 0.f));
	Draw2D::FormatStringToHandle(name_pos, "%s", body_color_, font_handle_, data_.name.c_str(), edge_color_);
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
	Draw2D::Circle(sub_screen_->GetCenterPos(), 33.f, GetColor(255, 255, 255), FALSE,3.f);
	sub_screen_->Down();

}