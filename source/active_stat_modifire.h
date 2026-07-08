#pragma once
#include"stat_modifire.h"

enum class StatType;
struct Status;
class VariableTimer;

class ActiveStatModifire
{
public:

	ActiveStatModifire();

	~ActiveStatModifire();

	void Init();

	void Update(const Status& base_status, Status& current_status);

	void Activation(const Status& base_status, Status& current_status,const StatModifire& effecacy_data);

	const bool GetIsActive() const;

private:

	void Release(const Status& base_status, Status& current_status);

private:

	// 効果時間を示してくれるタイマー
	std::shared_ptr<VariableTimer> timer_;
	
	StatModifire data_;
	bool is_active_;


};