#pragma once
#include"active_stat_modifire_ui.h"

class StatModifireUIGroup
{
public:

	StatModifireUIGroup(const std::string& file_path);

	~StatModifireUIGroup();

	void Init();

	void Update();

	void Draw();

private:

	void LoadFile(const std::string& file_path);

	void ChangeActiveStatModifireUI(int index);

private:

	const int kMaxStatModifireUINum = 5;

	std::unordered_map<int, ActiveStatModifireUI> active_stat_modifire_uis_;

	VECTOR base_pos_;

	float size_rate_;
	float rot_z_;

};