#pragma once
#include<random>

/// <summary>
/// ランダムの数字を返す(一様分布)
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="min">以上</param>
/// <param name="max">未満</param>
/// <returns></returns>
template <typename T>
inline T GetUniformRandom(const T& min,const T& max)
{
	static std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="average">平均値</param>
/// <param name="swing">振れ幅</param>
/// <returns></returns>
template <typename T>
inline T GetNormalRandom(const T& average,const T& swing)
{
	static std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(average, swing);
	return dis(gen);
}