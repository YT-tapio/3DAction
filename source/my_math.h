#pragma once

#include<math.h>

namespace MyMath
{
	
	inline float Clamp(const float& me, const float& min, const float& max)
	{
		float num = me;

		if (me < min) { num = min; }
		if (me > max) { num = max; }

		return num;
	}


}