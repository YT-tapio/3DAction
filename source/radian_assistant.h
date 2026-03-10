#pragma once
#define _USE_MATH_DEFINES
#include<math.h>

namespace RadianAssistant
{
	static const float kOneRad			= static_cast<float>(M_PI/180) * 1;
	static const float kReverceRad		= kOneRad * 180;

	//引数で受け取ったすうじのラジアン角を返す
	inline float TheNumRadian(const float num)
	{
		return kOneRad * num;
	}

	/// <summary>
	/// 調整した値を返す
	/// </summary>
	/// <param name="now_rad"></param>
	/// <param name="target_rad"></param>
	/// <param name="speed">delta_timeをすでにかけておく</param>
	/// <returns>now_rad + offset分</returns>
	inline float Lerp(const float& now_rad,const float& target_rad,const float& speed)
	{
		float value = now_rad; // 最終的に返す値
		if (now_rad == target_rad) { return value; }

		float now_target_diff = target_rad - now_rad;	// どれだけの差があるのか
		float norm_now_target_diff = now_target_diff / fabs(now_target_diff);
		// 差が180以上
		if (fabs(now_target_diff) > kReverceRad)
		{
			value = value - (norm_now_target_diff * speed);
			if(value > kReverceRad) 
			{ 
				value = value -  (kReverceRad * 2.f);
			}
			
			if (value < -kReverceRad) 
			{ 
				value = value + (kReverceRad * 2.f);
			}
		}
		else
		{
			value = value + (norm_now_target_diff * speed);
			// nowよりもtargetが低いとき
			if (now_rad > target_rad)
			{
				if (value < target_rad)
				{
					value = target_rad;
				}
			}
			else
			{
				if (value > target_rad)
				{
					value = target_rad;
				}
			}
		}

		

		return value;
	}

}

