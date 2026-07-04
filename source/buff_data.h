#pragma once
#include"condition_timer.h"
#include"variable_timer.h"
#include"buff_type.h"

struct BuffData
{
	float value;	// バフ量
	std::shared_ptr<VariableTimer> active_timer;	// このバフの有効時間
};

//struct BuffMasterData {
//public:
//	BuffMasterData(BuffType current_type, float rate_vlaue, float max_active_time) {
//		this->current_type = current_type;
//		this->rate_vlaue = rate_vlaue;
//		this->max_active_time = max_active_time;
//	}
//
//	BuffType GetBuffType() { return current_type; }
//	float GetRateVlaue() { return rate_vlaue; }
//	float GetMaxActiveTime() { return max_active_time; }
//
//private:
//	BuffType current_type;
//	float rate_vlaue;
//	float max_active_time;
//};

