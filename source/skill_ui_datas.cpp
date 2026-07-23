#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"skill_ui_datas.h"
#include"DxLib.h"
#include<functional>
#include"csv_file_assistant.h"

SkillUIDatas::SkillUIDatas()
{
	LoadFile();
}

SkillUIDatas::~SkillUIDatas()
{

}

const SkillUIData SkillUIDatas::GetData(const int skill_id) const
{
	auto skill_ui_data = skill_ui_datas_.find(skill_id);
	if (skill_ui_data == skill_ui_datas_.end())
	{
		SkillUIData empty;
		return empty;
	}
	return skill_ui_data->second;
}

void SkillUIDatas::LoadFile()
{
	// スキルid
	std::ifstream file("data/csv/ui/skill/skill_icon_name_data.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の行を飛ばす
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;

		auto id = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		auto icon_handle = LoadGraph(CSVFileAssistant::GetStringOfCSVFile(ss, data).c_str());
		if (icon_handle == -1) { printfDx("読み込み失敗\n"); }
		auto skill_name = CSVFileAssistant::GetStringOfCSVFile(ss, data);

		SkillUIData skill_ui_data;
		skill_ui_data.icon_handle = icon_handle;
		skill_ui_data.name = skill_name;
		skill_ui_datas_[id] = skill_ui_data;
	}
}