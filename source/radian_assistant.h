#pragma once
#define _USE_MATH_DEFINES
#include<math.h>

namespace RadianAssistant
{
	static const float kOneRad			= static_cast<float>(M_PI/180) * 1;
	static const float kReverceRad		= kOneRad * 180;

	//ˆø”‚Åó‚¯æ‚Á‚½‚·‚¤‚¶‚Ìƒ‰ƒWƒAƒ“Šp‚ğ•Ô‚·
	inline float TheNumRadian(const float num)
	{
		return kOneRad * num;
	}

}

