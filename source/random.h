#pragma once
#include<random>

/// <summary>
/// ƒ‰ƒ“ƒ_ƒ€‚Ì”š‚ğ•Ô‚·
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="min">ˆÈã</param>
/// <param name="max">–¢–</param>
/// <returns></returns>
template <typename T>
inline T GetRandom(const T& min,const T& max)
{
	static std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max - 1);
	return dis(gen);
}