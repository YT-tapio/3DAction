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

}