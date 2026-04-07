#pragma once

class SkillBase;
class Player;

class SkillLoader
{
public:

	static SkillLoader& GetInstance()
	{
		static SkillLoader instance;
		return instance;
	}

	SkillLoader(const SkillLoader&) = delete;
	SkillLoader& operator = (const SkillLoader&) = delete;

	std::shared_ptr<SkillBase> SkillLoad(const int skill_name, const std::string name, std::weak_ptr<Player> owner);

private:

	SkillLoader();

	void DecideFile(const int skill_name,std::string& file_path, int& skip_line_num);

	std::shared_ptr<SkillBase> MakeSkill(const int skill_name, std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner);

	std::shared_ptr<SkillBase> MakePunchSkill(std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner);

	std::shared_ptr<SkillBase> MakeAvoidSkill(std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner);

	std::shared_ptr<SkillBase> MakeAreaHealSkill(std::ifstream& file, std::string& line, const std::string name, std::weak_ptr<Player> owner);

};