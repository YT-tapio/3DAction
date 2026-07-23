#pragma once
#include"skill_ui_data.h"

class SkillUIDatas
{
public:

	SkillUIDatas();

	~SkillUIDatas();

	const SkillUIData GetData(const int skill_id) const;

private:

	void LoadFile();

private:

	std::unordered_map<int, SkillUIData> skill_ui_datas_;

};