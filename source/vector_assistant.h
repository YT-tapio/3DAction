#pragma once
#include"DxLib.h"

namespace VectorAssistant
{
	/// <summary>
	/// すべての要素が0のベクトル
	/// </summary>
	/// <returns></returns>
	inline const VECTOR VGetZero() 
	{
		return VGet(0.f, 0.f, 0.f);
	}

	/// <summary>
	/// 半分を返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	inline VECTOR VHerf(const VECTOR& vec)
	{
		return VScale(vec, 0.5f);
	}

	/// <summary>
	/// 要素がすべて引数と同じvecを返す
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	inline VECTOR VGetSame(const float& num)
	{
		return VGet(num, num, num);
	}

	/// <summary>
	/// 要素がすべて引数と同じvecを返す(2D)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	inline VECTOR VGetSame2D(const float& num)
	{
		return VGet(num, num, 0.f);
	}

	/// <summary>
	/// 引数の逆ベクトルを返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	inline VECTOR VGetReverce(const VECTOR&vec)
	{
		const float kReverceNum = -1.f;
		return VScale(vec, kReverceNum);
	}

	/// <summary>
	/// otherまでの向きを返す
	/// </summary>
	/// <param name="me"></param>
	/// <param name="other"></param>
	/// <returns></returns>
	inline VECTOR VGetDir(const VECTOR& me, const VECTOR& other)
	{
		return VNorm(VSub(other, me));
	}

	/// <summary>
	/// 平面の座標(yを無視した座標)を受け取る
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	inline VECTOR VGetFlat(const VECTOR& vec)
	{
		return VGet(vec.x, 0.f, vec.z);
	}

	inline float VGetDistSize(const VECTOR& vec, const VECTOR& vec2)
	{
		return VSize(VSub(vec, vec2));
	}

	inline float VGetTan(const VECTOR& vec)
	{
		float num = 0.f;

		// yはむし

		num = atan2f(vec.z, vec.x);

		return num;
	}

	/// <summary>
	/// 正射影ベクトル(meにうつる,otherの影)
	/// </summary>
	/// <param name="me"></param>
	/// <param name="other"></param>
	/// <returns></returns>
	inline VECTOR VGetProj(const VECTOR& me, const VECTOR& other)
	{
		VECTOR proj = VGet(0.f, 0.f, 0.f);

		//分母
		float denominator = 0.f;

		//vectorのサイズを受け取る

		float vec_size = VSize(me);

		denominator = vec_size * vec_size;

		//分子
		float molecule;

		molecule = VDot(me, other);

		float num = (molecule / denominator);

		proj = VScale(me, num);


		return proj;
	}

	/// <summary>
	/// 外積
	/// </summary>
	/// <param name="vec1"></param>
	/// <param name="vec2"></param>
	/// <returns></returns>
	inline VECTOR VGetCross(const VECTOR& vec1, const VECTOR& vec2)
	{
		VECTOR cross_vec = VGetZero();

		cross_vec.x = ((vec1.y * vec2.z) - (vec1.z * vec2.y));
		cross_vec.y = ((vec1.z * vec2.x) - (vec1.x * vec2.z));
		cross_vec.z = ((vec1.x * vec2.y) - (vec1.y * vec2.x));

		return cross_vec;
	}

	/// <summary>
	/// 二つの線分の距離を出す
	/// </summary>
	/// <param name="vec1"></param>
	/// <param name="vec2"></param>
	/// <param name="vec1_to_vec2_dist">1つめの始点から2つめの始点までの距離</param>
	/// <returns></returns>
	inline float VGetLineNearDist(const VECTOR& vec1, const VECTOR& vec2, const VECTOR& vec1_to_vec2_dist)
	{
		float near_dist_size = 0.f;

		//法線ベクトル
		VECTOR norm_vec = VGetCross(vec1, vec2);

		near_dist_size = VDot(norm_vec, vec1_to_vec2_dist);

		return near_dist_size;
	}

}