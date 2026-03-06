#pragma once
#include"DxLib.h"
#include"animation_data.h"

inline void LoadAnimation(AnimationData& data, const char name[], int ind, float play_speed, int priority,bool loop)
{
	data.handle = MV1LoadModel(name);
	if (data.handle == 1) { printfDx("ÉfÅ[É^ì«Ç›çûÇ›é∏îs\n"); }

	data.anim_index = ind;
	data.attach_index = 0;

	data.priority	= priority;

	data.play_time  = 0.f;
	data.total_time = 0.f;
	data.play_speed = play_speed;
	data.loop = loop;
}