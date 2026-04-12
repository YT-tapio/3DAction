#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"skill_loader.h"
#include"skill_base.h"
#include"punch_skill.h"
#include"avoid_skill.h"
#include"area_heal_skill.h"
#include"skill_name.h"
#include"player.h"
#include"sphere.h"
#include"vector_assistant.h"

SkillLoader::SkillLoader()
{

}

std::shared_ptr<SkillBase> SkillLoader::SkillLoad(const int skill_name, const std::string name, std::weak_ptr<Player> owner)
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

	skill = MakeSkill(skill_name, file, line, name,owner);

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
		file_path = file_path + "punch";
		skip_line_num = 1;
		break;

	case SkillName::kAvoid:
		// 回避のfile
		file_path = file_path + "avoid";
		skip_line_num = 1;
		break;

	case SkillName::kAreaHeal:
		// 範囲回復
		file_path = file_path + "area_heal";
		skip_line_num = 1;
		break;
	}
	file_path = file_path + "_data.csv";

}

std::shared_ptr<SkillBase> SkillLoader::MakeSkill(const int skill_name, std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner)
{
	std::shared_ptr<SkillBase> skill = nullptr;
	switch (skill_name)
	{
	case SkillName::kNothing:

		break;

	case SkillName::kPunch:

		skill = MakePunchSkill(file, line, name,owner);

		break;

	case SkillName::kAvoid:

		skill = MakeAvoidSkill(file, line, name,owner);

		break;

	case SkillName::kAreaHeal:

		skill = MakeAreaHealSkill(file, line, name,owner);

		break;
	}
	//printfDx("とっている\n");

	return skill;

}

std::shared_ptr<SkillBase> SkillLoader::MakePunchSkill(std::ifstream& file, std::string& line,const std::string name, std::weak_ptr<Player> owner)
{
	std::shared_ptr<SkillBase> skill = nullptr;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::getline(ss, data, ',');
		if (data != name) { continue; }

		float radius = 0.f;

		std::getline(ss, data, ',');
		radius = stof(data);
		auto owner_ptr = owner.lock();
		skill = std::make_shared<PunchSkill>(owner, owner_ptr->GetHandPos(), radius, owner_ptr->GetDetectionRadius());

		break;
	}
	return skill;
}

std::shared_ptr<SkillBase> SkillLoader::MakeAvoidSkill(std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner)
{
	std::shared_ptr<SkillBase> skill = nullptr;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::getline(ss, data, ',');
		if (data != name) { continue; }

		skill = std::make_shared<AvoidSkill>(owner);

		break;
	}
	return skill;
}

std::shared_ptr<SkillBase>SkillLoader::MakeAreaHealSkill(std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner)
{
	std::shared_ptr<SkillBase> skill = nullptr;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::getline(ss, data, ',');
		if (data != name) { continue; }
		float radius = 0.f;
		std::getline(ss, data, ',');
		radius = stof(data);
		
		auto owner_ptr = owner.lock();
		
		skill = std::make_shared<AreaHealSkill>(owner, owner_ptr->GetPosPtr(), radius);
		
		break;
	}

	return skill;
}