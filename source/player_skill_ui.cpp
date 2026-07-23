#include<sstream>
#include<fstream>
#include<string>
#include<functional>
#include"DxLib.h"
#include"player_skill_ui.h"
#include"csv_file_assistant.h"
#include"draw_2d.h"

PlayerSkillUI::PlayerSkillUI(const VECTOR& pos,const int font_handle,const int body_color,const int edge_color)
	: pos_(pos)
	, cool_time_ratio_(nullptr)
	, can_use_(nullptr)
	, font_handle_(font_handle)
	, body_color_(body_color)
	, edge_color_(edge_color)
{
	//LoadFile();
}

PlayerSkillUI::~PlayerSkillUI()
{

}

void PlayerSkillUI::Init()
{

}

void PlayerSkillUI::Update()
{

}

void PlayerSkillUI::Draw()
{
	// アイコンなどの描画
	Draw2D::RotaGraph(pos_, 1.f, 0.f, data_.icon_handle, TRUE);
	int icon_width = -1;
	int icon_height = -1;
	GetGraphSize(data_.icon_handle, &icon_width, &icon_height);
	VECTOR name_pos = VAdd(pos_, VGet(icon_width, 0.f, 0.f));
	Draw2D::FormatStringToHandle(name_pos, "%s", body_color_, font_handle_, data_.name.c_str(), edge_color_);
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