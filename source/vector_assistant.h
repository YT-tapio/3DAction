#pragma once
#include"DxLib.h"
#include"my_math.h"
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

	inline VECTOR VDevide(const VECTOR& vec,const float& num)
	{
		VECTOR result_vec = VGetZero();
		result_vec.x = vec.x / num;
		result_vec.y = vec.y / num;
		result_vec.z = vec.z / num;
		return result_vec;
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

	
	inline float VGetSegmentDist(const VECTOR& vec1_start_pos, const VECTOR& vec1_end_pos,const VECTOR& vec2_start_pos,const VECTOR& vec2_end_pos)
	{
		const float kScaleMax = 1.f;
		const float kScaleMin = 0.f;

		// この浮動小数点以下は0とみなす
		const float kZeroPoint = 0.00001f;

		float near_dist_size = 0.f;

		VECTOR vec1_segment				= VSub(vec1_end_pos, vec1_start_pos);	// 
		VECTOR vec2_segment				= VSub(vec2_end_pos, vec2_start_pos);	// 
		VECTOR vec1_to_vec2_start_pos	= VSub(vec1_start_pos, vec2_start_pos);	// 始点から始点までの距離

		float a = VDot(vec1_segment, vec1_segment);					// セグメントの2乗のサイズ
		float b = VDot(vec1_segment, vec2_segment);					// 
		float c = VDot(vec2_segment, vec2_segment);					// 
		float d = VDot(vec1_segment, vec1_to_vec2_start_pos);		// 
		float e = VDot(vec2_segment, vec1_to_vec2_start_pos);		// 

		float parallel_num = a * c - b * b;	// 平行かどうかを求めます
		float vec1_scale;					// vec1のセグメントの最短距離のposのscale値
		float vec2_scale;					// vec2のセグメントの最短距離のposのscale値
		if (parallel_num < kZeroPoint) 
		{ 
			vec1_scale = 0.0f; 
			vec2_scale = (b > c ? d / b : e / c); 
		} 
		else 
		{ 
			vec1_scale = (b * e - c * d) / parallel_num;
			vec2_scale = (a * e - b * d) / parallel_num;
		}

		vec1_scale = MyMath::Clamp(vec1_scale, kScaleMin, kScaleMax);		// 0～1の範囲で調整を行う
		vec2_scale = MyMath::Clamp(vec2_scale, kScaleMin, kScaleMax);		// 0～1の範囲で調整を行う

		VECTOR vec1_near_pos = VAdd(vec1_start_pos, VScale(vec1_segment, vec1_scale));
		VECTOR vec2_near_pos = VAdd(vec2_start_pos, VScale(vec2_segment, vec2_scale));

		near_dist_size = VSize(VSub(vec2_near_pos, vec1_near_pos));

		return near_dist_size;
	}

	/// <summary>
	/// 二つのベクトルが平行かどうか
	/// </summary>
	/// <param name="vec1"></param>
	/// <param name="vec2"></param>
	/// <return></return>
	inline bool IsParallel(const VECTOR& vec1, const VECTOR& vec2)
	{
		// 正規化
		VECTOR norm_vec1 = VNorm(vec1);
		VECTOR norm_vec2 = VNorm(vec2);

		// 内積
		float num = VDot(norm_vec1, norm_vec2);
		return (num == 1.f);
	}

}