#pragma once
#include"active_stat_modifire_ui.h"
#include"stat_type.h"
#include"modifire_operation.h"

class StatModifireUIGroup
{
public:

	StatModifireUIGroup(const std::string& file_path);

	~StatModifireUIGroup();

	void Init();

	void Update();

	void Draw();

	void Spawn(std::function<bool()> end_condition, StatType stat_type, ModifireOperation operation);

private:

	void LoadFile(const std::string& file_path);

	void ChangeActiveStatModifireUI(int index);

private:

	const int kMaxStatModifireUINum = 5;

	int handle_;

	std::unordered_map<int, ActiveStatModifireUI> active_stat_modifire_uis_;

	VECTOR base_pos_;

	float size_rate_;
	float rot_z_;

};