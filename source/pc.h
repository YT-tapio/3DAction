#pragma once
#include"input_state.h"
const int kMaxKeyNum = 256;
const int kMaxMouseNum = 3;
struct InputState;

class PC
{
public:

	PC();

	~PC();

	void Init();

	void Debug();

	/// @brief 更新
	void Update();

	/// @brief どのくらい入力されているかを時間で返す(key)
	/// @param key_code 
	/// @return 時間(秒)
	float GetPushingTimeKey(int key_code);

	/// <summary>
	/// マウスがどれくらい入力されているかを返す
	/// </summary>
	/// <returns></returns>
	float GetPushingTimeMouseButton(int mouse_code);

	/// @brief どのくらい話しているのかを時間で返す
	/// @param key_code 
	/// @return 時間(秒)
	float GetReleaseTimeKey(int key_code);

	float GetReleaseTimeMouseButton(int mouse_code);


private:

	InputState key_state_[kMaxKeyNum];
	InputState mouse_state_[kMaxMouseNum];

	/// <summary>
	/// キーのアップデート
	/// </summary>
	void KeyUpdate();

	void MouseUpdate();

	int GetMouseButtonNum(int mouse_num);

};