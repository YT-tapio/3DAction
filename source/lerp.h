#pragma once
#include<math.h>
#include"DxLib.h"
#include"vector_assistant.h"

namespace Lerp
{
	/// <summary>
	/// 
	/// </summary>
	/// <param name="now"></param>
	/// <param name="target"></param>
	/// <param name="speed">変化量(マイナスはダメ)</param>
	/// <returns></returns>
	inline float Lerpf(const float& now, const float& target, const float& speed)
	{
		float value = 0.f;

		float diff = target - now;

		if (fabs(diff) > speed)
		{
			value = (diff / fabs(diff)) * speed;
		}
		else
		{
			value = diff;
		}
		value = now + value;
		return value;
	}

	/// <summary>
	/// だんだんと遅くなる
	/// </summary>
	/// <param name="now"></param>
	/// <param name="target"></param>
	/// <param name="speed">0～1の間</param>
	/// <returns></returns>
	inline float Dampf(const float& now, const float& target, const float& speed)
	{
		float value = 0.f;

		float diff = target - now;

		value = (diff * speed) + now;
		
		return value;
	}

	/// <summary>
	/// 等速
	/// </summary>
	/// <param name="now"></param>
	/// <param name="target"></param>
	/// <param name="speed">どれだけ変化するのか(まいなすはだめ)</param>
	/// <returns>等速の移動値</returns>
	inline VECTOR LerpV(const VECTOR& now, const VECTOR& target,const float& speed)
	{
		VECTOR value = VectorAssistant::VGetZero();

		VECTOR dist = VSub(target,now);

		if (VSize(dist) > speed)
		{
			value = VScale(VNorm(dist), speed);	//speed分の移動量
		}
		else
		{
			value = dist;	//speed分いどうしてしまうとおいこしてしまうので
		}
		value = VAdd(now, value);
		return value;
	}

	/// <summary>
	/// now～target間のspeed分調整した移動値が返される
	/// </summary>
	/// <param name="now"></param>
	/// <param name="target"></param>
	/// <param name="speed">0～1の間</param>
	/// <returns>最初が最高速度の移動値</returns>
	inline VECTOR DampV(const VECTOR& now, const VECTOR& target, const float& speed)
	{
		VECTOR value = VectorAssistant::VGetZero();
		VECTOR diff = VSub(target, now);
		value = VAdd(now,VScale(diff, speed));
		return value;
	}
}
