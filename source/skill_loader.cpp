#include"DxLib.h"
#include<memory>
#include<fstream>
#include<sstream>
#include"skill_loader.h"
#include"skill_base.h"
#include"avoid_skill.h"
#include"skill_name.h"

SkillLoader::SkillLoader()
{

}

std::shared_ptr<SkillBase> SkillLoader::SkillLoad(const int skill_name, const std::string name)
{
	std::string file_path = "data/csv/skill/";
	std::shared_ptr<SkillBase> skill = nullptr;
	int skip_line_num = 0;

	DecideFile(skill_name, file_path, skip_line_num);

	std::ifstream file(file_path);
	std::string line;
	if (!file) 
	{
		printfDx("csvファイル : 読み込み失敗\n");
		return skill;
	}

	// 何行飛ばすのか
	for (int i = 0; i < skip_line_num; i++)
	{
		std::getline(file, line);
	}

	skill = MakeSkill(skill_name, file, line, name);

	return skill;
}

void SkillLoader::DecideFile(const int skill_name,std::string& file_path, int& skip_line_num)
{
	switch (skill_name)
	{
	case SkillName::kNothing:
		
		break;

	case SkillName::kPunch:
		// パンチのfile
		file_path = file_path + "punch_data";
		skip_line_num = 1;
		break;

	case SkillName::kAvoid:
		// 回避のfile
		file_path = file_path + "avoid_data";
		skip_line_num = 1;
		break;

	case SkillName::kAreaHeal:
		// 範囲回復
		file_path = file_path + "area_heal_data";
		skip_line_num = 1;
		break;
	}
	file_path = file_path + ".csv";

}

std::shared_ptr<SkillBase> SkillLoader::MakeSkill(const int skill_name, std::ifstream& file, std::string& line, const std::string name)
{
	std::shared_ptr<SkillBase> skill = nullptr;
	switch (skill_name)
	{
	case SkillName::kNothing:

		break;

	case SkillName::kPunch:

		skill = MakePunchSkill(file, line, name);

		break;

	case SkillName::kAvoid:

		skill = MakeAvoidSkill(file, line, name);

		break;

	case SkillName::kAreaHeal:

		skill = MakeAreaHealSkill(file, line, name);

		break;
	}
	printfDx("とっている\n");

	return skill;

}

std::shared_ptr<SkillBase> SkillLoader::MakePunchSkill(std::ifstream& file, std::string& line,const std::string name)
{
	std::shared_ptr<SkillBase> skill = nullptr;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::getline(ss, data, ',');
		if (data != name) { continue; }

		// ちゃんとここまでとおってきていて感動

		break;
	}
	return skill;
}

std::shared_ptr<SkillBase> SkillLoader::MakeAvoidSkill(std::ifstream& file, std::string& line, const std::string name)
{
	std::shared_ptr<SkillBase> skill = nullptr;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::getline(ss, data, ',');
		if (data != name) { continue; }

		

		break;
	}
	return skill;
}

std::shared_ptr<SkillBase>SkillLoader::MakeAreaHealSkill(std::ifstream& file, std::string& line, const std::string name)
{
	std::shared_ptr<SkillBase> skill = nullptr;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::getline(ss, data, ',');
		if (data != name) { continue; }

		break;
	}

	return skill;
}