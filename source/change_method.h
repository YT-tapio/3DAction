#pragma once
#include <cstdint>

/// <summary>
/// 変化の仕方
/// </summary>
enum class ChangeMethod : uint8_t	//uint8_tでenumclassを8bitにした。（つけないと32bit使うので無駄がある）
{
	kMoment,
	kLerp,
	kDamp
};