#pragma once

enum class EffecacyCategory;
struct Status;
struct EffecacyData;
class VariableTimer;


class EffecacyAdaptation
{
public:

	EffecacyAdaptation();

	~EffecacyAdaptation();

	void Init();

	void Update(const Status& base_status, Status& current_status);

	void Adaptation(const Status& base_status, Status& current_status,const EffecacyData& effecacy_data);

private:

	void Release(const Status& base_status, Status& current_status);

private:

	// 効果時間を示してくれるタイマー
	std::shared_ptr<VariableTimer> timer_;
	
	EffecacyData data_;
	bool is_active_;


};