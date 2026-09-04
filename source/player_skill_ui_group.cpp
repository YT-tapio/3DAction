#include<fstream>
#include<sstream>
#include<memory>
#include<string>
#include<functional>
#include"DxLib.h"
#include"player_skill_ui_group.h"
#include"vector_assistant.h"
#include"csv_file_assistant.h"
#include"font.h"
#include"skill_ui_datas.h"
#include"config_name.h"

PlayerSkillUIGroup::PlayerSkillUIGroup()
	: normal_skill_pos_(VectorAssistant::VGetZero())
	, strong_skill_pos_(VectorAssistant::VGetZero())
	, font_handle_(-1)
	, body_color_(-1)
	, edge_color_(-1)
{
	// fontをダウンロード
	LoadFile();
	normal_skill_ui_ = std::make_shared<PlayerSkillUI>(normal_skill_pos_, font_handle_, body_color_, edge_color_, ConfigName::normal_skill);
	strong_skill_ui_ = std::make_shared<PlayerSkillUI>(strong_skill_pos_,font_handle_, body_color_, edge_color_, ConfigName::strong_skill);
	
	//normal_skill_ui_ = nullptr;
	//strong_skill_ui_ = nullptr;
	
	skill_ui_datas_ = std::make_shared<SkillUIDatas>();
	//skill_ui_datas_ = nullptr;
}

PlayerSkillUIGroup::~PlayerSkillUIGroup()
{
	DeleteFontToHandle(font_handle_);
	DeleteGraph(normal_skill_input_handle_);
	DeleteGraph(strong_skill_input_handle_);
}

void PlayerSkillUIGroup::Init()
{

}

void PlayerSkillUIGroup::Update()
{
	if (normal_skill_ui_ != nullptr)
	{
		normal_skill_ui_->Update();
	}
	if (strong_skill_ui_ != nullptr)
	{
		strong_skill_ui_->Update();
	}
}

void PlayerSkillUIGroup::Draw()
{
	if (normal_skill_ui_ != nullptr)
	{
		normal_skill_ui_->Draw();
	}
	if (strong_skill_ui_ != nullptr)
	{
		strong_skill_ui_->Draw();
	}
}

void PlayerSkillUIGroup::ChangeSkill(const int normal_skill_id, std::function<float()> normal_skill_cool_time_ratio, std::function<bool()> normal_skill_can_use
	, const int strong_skill_id, std::function<float()> strong_skill_cool_time_ratio, std::function<bool()> strong_skill_can_use)
{

	SkillUIData normal_skill_data;
	SkillUIData strong_skill_data;
	//SkillUIData 
	if (skill_ui_datas_ != nullptr)
	{
		normal_skill_data = skill_ui_datas_->GetData(normal_skill_id);
		strong_skill_data = skill_ui_datas_->GetData(strong_skill_id);
	}

	// データを取得
	if (normal_skill_ui_ != nullptr)
	{
		normal_skill_ui_->SetSkill(normal_skill_data, normal_skill_cool_time_ratio, normal_skill_can_use);
	}

	if (strong_skill_ui_ != nullptr)
	{
		strong_skill_ui_->SetSkill(strong_skill_data, strong_skill_cool_time_ratio, strong_skill_can_use);
	}
	
}


void PlayerSkillUIGroup::LoadFile()
{
	
	std::ifstream file("data/csv/ui/skill/skill_ui_data.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の行を飛ばす
	std::getline(file, line);
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;

		normal_skill_pos_ = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		strong_skill_pos_ = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		auto normal_skill_input_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		auto strong_skill_input_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		normal_skill_input_handle_ = LoadGraph(normal_skill_input_path.c_str());
		strong_skill_input_handle_ = LoadGraph(strong_skill_input_path.c_str());
		//normal_skill_input_handle_ = -1;
		//strong_skill_input_handle_ = -1;
		if (normal_skill_input_handle_ == -1) { printfDx("読み込み失敗\n"); }
		if (strong_skill_input_handle_ == -1) { printfDx("読み込み失敗\n"); }
		auto font_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		font_handle_ = Font::CreateHandleOfFile(font_path);
		//font_handle_ = -1;
		body_color_ = CSVFileAssistant::GetColorOfCSVFile(ss, data);
		edge_color_ = CSVFileAssistant::GetColorOfCSVFile(ss, data);


	}
}