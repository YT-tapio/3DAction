#pragma once
#include"input_state.h"
const int kMaxKeyNum = 256;

struct InputState;

class PC
{
public:

	PC();

	~PC();

	void Init();

	/// @brief XV
	void Update();

	/// @brief ‚Ç‚Ì‚­‚ç‚¢“ü—Í‚³‚ê‚Ä‚¢‚é‚©‚ğŠÔ‚Å•Ô‚·(key)
	/// @param key_code 
	/// @return ŠÔ(•b)
	float GetPushingTimeKey(int key_code);


	float GetPushingTimeMouseButton();

	/// @brief ‚Ç‚Ì‚­‚ç‚¢˜b‚µ‚Ä‚¢‚é‚Ì‚©‚ğŠÔ‚Å•Ô‚·
	/// @param key_code 
	/// @return ŠÔ(•b)
	float GetReleaseTimeKey(int key_code);

	float GetReleaseTimeKey(int key?cc);


private:

	InputState state_[kMaxKeyNum];

};