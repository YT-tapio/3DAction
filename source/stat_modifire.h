#pragma once
#include"modifire_operation.h"
#include"stat_type.h"

struct StatModifire
{
	float rate = 0.f;					// バフの量(0～1)
	float time = 0.f;					// 適応する時間
	EfficacyType type = EfficacyType::kEmpty;			// バフかデバフか
	StatType category = StatType::kEmpty;	// 効果を会得する種類
};