#pragma once
#include"DxLib.h"
#include"my_math.h"
#include"radian_assistant.h"
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

	inline const VECTOR VGet2D(const float& x,const float& y)
	{
		return VGet(x, y, 0.f);
	}

	//num分割ってくれる 
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
	/// y軸回転させた時のvector(ラジアン角ではなく実数値)
	/// </summary>
	/// <param name="me"></param>
	/// <param name="num">(-3.14～3.14)</param>
	/// <returns></returns>
	inline VECTOR VGetRotPiY(const VECTOR& me, const float num)
	{
		VECTOR value = VGetZero();

		value.x = (me.x * cosf(num)) + (me.z * sinf(num));
		value.y = me.y;
		value.z = (-me.x * sinf(num)) + (me.z * cosf(num));

		return value;
	}
	
	/// <summary>
	/// rotationからdirを受け取る
	/// </summary>
	/// <param name="rot"></param>
	/// <returns></returns>
	inline VECTOR VGetDirFromRotY(const VECTOR& rot)
	{
		VECTOR vel = VGetZero();
		vel.x = sinf(rot.y);
		vel.z = cosf(rot.y);

		return VGetReverce(vel);
	}

	/// <summary>
	/// matrixからpositionをとる
	/// </summary>
	/// <param name="mat"></param>
	/// <returns></returns>
	inline VECTOR VGetPositionFromMatrix(const MATRIX& mat)
	{
		VECTOR vec = VGetZero();
		vec.x = mat.m[3][0];
		vec.y = mat.m[3][1];
		vec.z = mat.m[3][2];
		return vec;
	}

	/// <summary>
	/// y軸回転したときのvector
	/// </summary>
	/// <param name="me">子のベクトルを回転</param>
	/// <param name="rad">ラジアン角(-180～180)</param>
	/// <returns></returns>
	inline VECTOR VGetRotRadY(const VECTOR& me, const float rad)
	{
		return VGetRotPiY(me, RadianAssistant::kOneRad * rad);
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

	/// <summary>
	/// xとzの平衡の回転量
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	inline float VGetTan(const VECTOR& vec)
	{
		float num = 0.f;

		// yはむし
		num = atan2f(vec.x, vec.z);
		return num;
	}

	/// <summary>
	/// vector同士での値の調整
	/// </summary>
	/// <param name="me"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	inline VECTOR VMax(const VECTOR& me, const VECTOR& max)
	{
		return (VSize(me) > VSize(max)) ? max : me;
	}

	/// <summary>
	/// vector同士での値の調整
	/// </summary>
	/// <param name="me"></param>
	/// <param name="min"></param>
	/// <returns></returns>
	inline VECTOR VMin(const VECTOR& me, const VECTOR& min)
	{
		return (VSize(me) < VSize(min)) ? min : me;
	}

	/// <summary>
	/// vector同士での値の調整
	/// </summary>
	/// <param name="me"></param>
	/// <param name="max"></param>
	/// <param name="min"></param>
	/// <returns></returns>
	inline VECTOR VClamp(const VECTOR& me, const VECTOR& max, const VECTOR min)
	{
		VECTOR value = me;

		value = VMax(me, max);
		value = VMin(me, min);

		return value;
	}

	/// <summary>
	/// float型でvectorの値を調整
	/// </summary>
	/// <param name="me"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	inline VECTOR VMaxf(const VECTOR& me, const float max)
	{
		return (VSize(me) > max) ? VScale(VNorm(me), max) : me;
	}

	/// <summary>
	/// float型でvectorの値を調整
	/// </summary>
	/// <param name="me"></param>
	/// <param name="min"></param>
	/// <returns></returns>
	inline VECTOR VMinf(const VECTOR& me, const float min)
	{
		return (VSize(me) < min) ? VScale(VNorm(me), min) : me;
	}

	/// <summary>
	/// float型での値を調整
	/// </summary>
	/// <param name="me"></param>
	/// <param name="max"></param>
	/// <param name="min"></param>
	/// <returns></returns>
	inline VECTOR VClampf(const VECTOR& me, const float max,const float min)
	{
		VECTOR value = me;

		value = VMaxf(me, max);
		value = VMinf(me, min);

		return value;
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

		// 分母
		float denominator = 0.f;
		// vectorのサイズを受け取る
		float vec_size = VSize(me);
		denominator = vec_size * vec_size;

		// 分子
		float molecule = 0.f;
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
	/// セグメント同士のの距離をvectorで返す
	/// </summary>
	/// <param name="vec1_start_pos"></param>
	/// <param name="vec1_end_pos"></param>
	/// <param name="vec2_start_pos"></param>
	/// <param name="vec2_end_pos"></param>
	/// <returns></returns>
	inline VECTOR VGetSegmentDist(const VECTOR& vec1_start_pos, const VECTOR& vec1_end_pos, const VECTOR& vec2_start_pos, const VECTOR& vec2_end_pos)
	{
		VECTOR dist = VectorAssistant::VGetZero();

		const float kScaleMax = 1.f;
		const float kScaleMin = 0.f;

		// この浮動小数点以下は0とみなす
		const float kZeroPoint = 0.00001f;

		VECTOR vec1_segment = VSub(vec1_end_pos, vec1_start_pos);	// 
		VECTOR vec2_segment = VSub(vec2_end_pos, vec2_start_pos);	// 
		VECTOR vec1_to_vec2_start_pos = VSub(vec1_start_pos, vec2_start_pos);	// 始点から始点までの距離

		float a = VDot(vec1_segment, vec1_segment);					// セグメントの2乗のサイズ
		float b = VDot(vec1_segment, vec2_segment);					// 
		float c = VDot(vec2_segment, vec2_segment);						// 
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

		dist = VSub(vec2_near_pos, vec1_near_pos);

		return dist;
	}
	
	/// <summary>
	/// セグメント同士の距離を返す
	/// </summary>
	/// <param name="vec1_start_pos"></param>
	/// <param name="vec1_end_pos"></param>
	/// <param name="vec2_start_pos"></param>
	/// <param name="vec2_end_pos"></param>
	/// <returns></returns>
	inline float VGetSegmentDistSize(const VECTOR& vec1_start_pos, const VECTOR& vec1_end_pos,const VECTOR& vec2_start_pos,const VECTOR& vec2_end_pos)
	{
		float near_dist_size = 0.f;

		near_dist_size = VSize(VGetSegmentDist(vec1_start_pos, vec1_end_pos, vec2_start_pos, vec2_end_pos));
		return near_dist_size;
	}

	/// <summary>
	/// 二つのベクトルが平行かどうか
	/// </summary>
	/// <param name="vec1">正規化しなくてもいい</param>
	/// <param name="vec2">正規化しなくてもいい</param>
	/// <return></return>
	inline bool IsParallel(const VECTOR& vec1, const VECTOR& vec2)
	{
		const float kParallelNum = 1.f;

		// 正規化
		VECTOR norm_vec1 = VNorm(vec1);
		VECTOR norm_vec2 = VNorm(vec2);

		// 内積
		float num = VDot(norm_vec1, norm_vec2);
		return (num == kParallelNum);
	}

	/// <summary>
	/// 同じ向き
	/// </summary>
	/// <param name="vec1">正規化しなくてもいい</param>
	/// <param name="vec2">正規化しなくてもいい</param>
	/// <returns></returns>
	inline bool IsSameDir(const VECTOR& vec1, const VECTOR& vec2)
	{
		const float kSameDirNum = 0.999f;

		// 正規化
		VECTOR norm_vec1 = VNorm(vec1);
		VECTOR norm_vec2 = VNorm(vec2);

		// 内積
		float dot = VDot(norm_vec1, norm_vec2);
		return (dot > kSameDirNum);
	}

	inline bool IsSamePos(const VECTOR& vec1, const VECTOR& vec2)
	{
		// 許容範囲
		const float kToleranceRange = 1e-4f;

		VECTOR diff = VSub(vec1, vec2);
		return VSize(diff) < kToleranceRange;
	}

	/// <summary>
	/// 要素が0
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	inline bool IsEmpty(const VECTOR& vec)
	{
		return (VSize(vec) < 0.01f);
	}

	 
	// 正規化しなくてもいい
	inline float GetTwoVectorRad(const VECTOR& vec1, const VECTOR& vec2)
	{
		VECTOR vec1_norm = VNorm(vec1);
		VECTOR vec2_norm = VNorm(vec2);

		float dot_num = VDot(vec1_norm, vec2_norm);
		float rad_num = acosf(dot_num);

		return rad_num;
	}

}