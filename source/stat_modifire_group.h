#pragma once

class ActiveStatModifire;
class IPlayerUIGroup;

class ActiveStatModifireGroup
{
public:

	ActiveStatModifireGroup();

	~ActiveStatModifireGroup();

	void Init();

	void Update(const Status& base_status, Status& current_status);

	/// <summary>
	/// 引数のバフを発動する
	/// </summary>
	void Activation(const Status& base_status, Status& current_status, const std::string& name, std::shared_ptr<IPlayerUIGroup> player_ui_group);

private:

	static const int kMaxStatModifire = 20;

	// vectorでデータの確保
	std::vector<std::shared_ptr<ActiveStatModifire>> active_stat_modifires_;

};
