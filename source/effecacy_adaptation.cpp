#include<memory>"
#include"effecacy_data.h"
#include"effecacy_adaptation.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"status.h"

EffecacyAdaptation::EffecacyAdaptation()
{

}

EffecacyAdaptation::~EffecacyAdaptation()
{

}

void EffecacyAdaptation::Init()
{

}

void EffecacyAdaptation::Update(const Status& base_status,Status& current_status)
{
	// 効果量
	float effecacy_num = 0.f;

	timer_->Update();

	// タイマーが終了したタイミング
	if (timer_->GetIsEnd())
	{
		switch (data_.category)
		{
		case EffecacyCategory::kPhysicalATK:
			current_status.physical_atk -= base_status.physical_atk * data_.rate;
			break;

		case EffecacyCategory::kPhysicalDEF:
			current_status.physical_def -= base_status.physical_def * data_.rate;
			break;

		case EffecacyCategory::kMagicATK:
			current_status.magic_atk -= base_status.magic_atk * data_.rate;
			break;

		case EffecacyCategory::kMagicDEF:
			current_status.magic_def -= base_status.magic_def * data_.rate;
			break;

		default:
			break;
		}
	}

}

void EffecacyAdaptation::Release(const Status& base_status, Status& current_status)
{

}


void EffecacyAdaptation::Adaptation(const Status& base_status, Status& current_status, const EffecacyData& effecacy_data)
{
	// この瞬間に効果を発揮させる
	data_ = effecacy_data;

	switch (data_.category)
	{
	case EffecacyCategory::kPhysicalATK:
		current_status.physical_atk += base_status.physical_atk * data_.rate;
		break;

	case EffecacyCategory::kPhysicalDEF:
		current_status.physical_def += base_status.physical_def * data_.rate;
		break;

	case EffecacyCategory::kMagicATK:
		current_status.magic_atk += base_status.magic_atk * data_.rate;
		break;

	case EffecacyCategory::kMagicDEF:
		current_status.magic_def += base_status.magic_def * data_.rate;
		break;

	default:
		break;
	}

}