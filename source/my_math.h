#pragma once

#include<math.h>

namespace MyMath
{
	
	inline int Clamp(const int& me, const int& min, const int& max)
	{
		int num = me;

		if (me < min) { num = min; }
		if (me > max) { num = max; }

		return num;
	}

	inline float Clampf(const float& me, const float& min, const float& max)
	{
		if (me < min) { return min; }
		if (me > max) { return max; }
		return me;
	}



}