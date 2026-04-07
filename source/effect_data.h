#pragma once

struct EffectData
{
	std::string path;		// 
	int handle;				// 

	VECTOR pos;			// 
	VECTOR rot;			// 
	VECTOR scale;		// 

	float speed;			// 
	float play_time;		// 
	float total_time;		// 

	bool loop;				// 
};