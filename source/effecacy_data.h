#pragma once
#include"effecacy_type.h"
#include"effecacy_category.h"

struct EffecacyData
{
	float rate;					// バフの量(0～1)
	float time;					// 適応する時間
	EffecacyType type;			// バフかデバフか
	EffecacyCategory category;	// 効果を会得する種類
};