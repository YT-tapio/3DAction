#include<iostream>
#include<memory>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include"DxLib.h"
#include"skill_loader.h"
#include"skill_base.h"
#include"punch_skill.h"
#include"punch.h"
#include"avoid_skill.h"
#include"area_heal_skill.h"
#include"skill_name.h"
#include"player.h"
#include"sphere.h"
#include"vector_assistant.h"
#include"csv_file_assistant.h"
#include"combo_action.h"
#include"combo.h"
#include"combo_skill.h"
#include"rigid_body.h"


std::shared_ptr<SkillBase> MakePunchSkill(std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner)
{
	std::shared_ptr<SkillBase> skill = nullptr;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::getline(ss, data, ',');
		if (data != name) { continue; }
		bool is_right = CSVFileAssistant::GetBoolOfCSVFile(ss, data);
		std::string anim_name = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		float min_coll_ratio = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		float max_coll_ratio = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		float radius = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		float approach_speed = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		float approach_ratio = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		float cool_time = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		auto owner_ptr = owner.lock();

		// right
		if (is_right)
		{
			skill = std::make_shared<PunchSkill>(owner, owner_ptr->GetRightHandPos(), anim_name, radius, min_coll_ratio, max_coll_ratio, owner_ptr->GetDetectionRadius(), approach_speed, approach_ratio, cool_time);
		}
		else
		{
			skill = std::make_shared<PunchSkill>(owner, owner_ptr->GetLeftHandPos(), anim_name, radius, min_coll_ratio, max_coll_ratio, owner_ptr->GetDetectionRadius(), approach_speed, approach_ratio, cool_time);
		}

		break;
	}
	return skill;
}

std::shared_ptr<SkillBase> MakeAvoidSkill(std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner)
{
	std::shared_ptr<SkillBase> skill = nullptr;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::getline(ss, data, ',');
		if (data != name) { continue; }

		float speed = CSVFileAssistant::GetFloatOfCSVFile(ss, data);

		//skill = std::make_shared<AvoidSkill>(owner,speed);

		break;
	}
	return skill;
}

std::shared_ptr<SkillBase> MakeAreaHealSkill(std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner)
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
		float cool_time = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		auto owner_ptr = owner.lock();

		skill = std::make_shared<AreaHealSkill>(owner, owner_ptr->GetPosPtr(), radius, cool_time);

		break;
	}

	return skill;
}

std::shared_ptr<SkillBase> MakeComboAttackSkill(std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner)
{
	const std::string kSame = "same";
	std::shared_ptr<SkillBase> skill = nullptr;
	// targetがあるかどうか
	bool is_target = FALSE;
	int combo_num = 0;	// コンボ数
	std::unordered_map<int, std::shared_ptr<Combo>> combos;
	float approach_speed = 0.45f;
	float approach_ratio = 0.3f;
	std::unordered_map<int, std::pair<float, float>> id_approach_speed_ratio_mp;
	float cool_time = 0.f;
	VECTOR* hand_pos;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう
		std::string name_data = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		if (is_target)
		{
			if (name_data != kSame) { break; }
		}
		else
		{
			if (name_data != name) { continue; }
			is_target = TRUE;
		}

		int skill_id = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		std::shared_ptr<Combo> combo = nullptr;
		switch (skill_id)
		{
		case SkillName::kPunch:

			std::pair<float, float> approach_speed_ratio;
			bool is_right = CSVFileAssistant::GetIntOfCSVFile(ss, data);
			std::string anim_name = CSVFileAssistant::GetStringOfCSVFile(ss, data);
			float min_ratio_next_combo = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			float max_ratio_next_combo = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			float min_coll_ratio = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			float max_coll_ratio = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			float go_next_timing = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			float radius = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			float mass = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			float friction = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			float approach_speed = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			float approach_ratio = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			cool_time = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
			auto owner_ptr = owner.lock();
			approach_speed_ratio = { approach_speed,approach_ratio };

			hand_pos = is_right ? owner_ptr->GetRightHandPos() : owner_ptr->GetLeftHandPos();
			const auto rigid_body = std::make_shared<RigidBody>(std::make_shared<Sphere>(radius, VectorAssistant::VGetZero()), hand_pos, FALSE, TRUE, mass, friction);
			const auto punch = std::make_shared<Punch>(owner, hand_pos, anim_name, min_coll_ratio, max_coll_ratio, rigid_body);
			combo = std::make_shared<Combo>(owner, min_coll_ratio, max_coll_ratio, go_next_timing, anim_name, punch);

			id_approach_speed_ratio_mp[combo_num] = approach_speed_ratio;

			break;
		}

		combos[combo_num] = combo;
		combo_num++;
	}

	if (is_target)
	{
		skill = std::make_shared<ComboSkill>(owner,
			std::make_shared<ComboAction>(owner, combos), id_approach_speed_ratio_mp, cool_time);
	}

	return skill;
}



void DecideFile(const int skill_name, std::string& file_path, int& skip_line_num)
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

	case SkillName::kcomboAttack:
		// 範囲回復
		file_path = file_path + "combo_attack";
		skip_line_num = 1;
		break;

	}
	file_path = file_path + "_data.csv";

}

std::shared_ptr<SkillBase> MakeSkill(const int skill_name, std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner)
{
	std::shared_ptr<SkillBase> skill = nullptr;
	switch (skill_name)
	{
	case SkillName::kNothing:

		break;

	case SkillName::kPunch:

		skill = MakePunchSkill(file, line, name, owner);

		break;

	case SkillName::kAvoid:

		skill = MakeAvoidSkill(file, line, name, owner);

		break;

	case SkillName::kAreaHeal:

		skill = MakeAreaHealSkill(file, line, name, owner);

		break;

	case SkillName::kcomboAttack:

		skill = MakeComboAttackSkill(file, line, name, owner);

		break;
	}
	//printfDx("とっている\n");

	return skill;

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

