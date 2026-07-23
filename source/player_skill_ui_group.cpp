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

PlayerSkillUIGroup::PlayerSkillUIGroup()
	: normal_skill_pos_(VectorAssistant::VGetZero())
	, strong_skill_pos_(VectorAssistant::VGetZero())
	, font_handle_(-1)
	, body_color_(-1)
	, edge_color_(-1)

{
	// fontをダウンロード
	LoadFile();

	normal_skill_ui_ = std::make_shared<PlayerSkillUI>(normal_skill_pos_, font_handle_, body_color_, edge_color_);
	strong_skill_ui_ = std::make_shared<PlayerSkillUI>(strong_skill_pos_, font_handle_, body_color_, edge_color_);
	skill_ui_datas_ = std::make_unique<SkillUIDatas>();
	// いったん最初にデータを挿入
	ChangeSkill(0, nullptr, nullptr, 3, nullptr, nullptr);
}

PlayerSkillUIGroup::~PlayerSkillUIGroup()
{

}

void PlayerSkillUIGroup::Init()
{

}

void PlayerSkillUIGroup::Update()
{

}

void PlayerSkillUIGroup::Draw()
{
	normal_skill_ui_->Draw();
	strong_skill_ui_->Draw();
}

void PlayerSkillUIGroup::ChangeSkill(const int normal_skill_id, std::function<float()> normal_skill_cool_time_ratio, std::function<bool()> normal_skill_can_use
	, const int strong_skill_id, std::function<float()> strong_skill_cool_time_ratio, std::function<bool()> strong_skill_can_use)
{
	// スキルの切り替え

	// データを取得
	auto normal_skill_data = skill_ui_datas_->GetData(normal_skill_id);
	auto strong_skill_data = skill_ui_datas_->GetData(strong_skill_id);

	normal_skill_ui_->SetSkill(normal_skill_data,normal_skill_cool_time_ratio,normal_skill_can_use);
	strong_skill_ui_->SetSkill(strong_skill_data,strong_skill_cool_time_ratio,strong_skill_can_use);
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
		font_handle_ = Font::CreateHandleOfFile(CSVFileAssistant::GetStringOfCSVFile(ss, data).c_str());
		body_color_ = CSVFileAssistant::GetColorOfCSVFile(ss, data);
		edge_color_ = CSVFileAssistant::GetColorOfCSVFile(ss, data);
	}
}