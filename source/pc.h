#pragma once
#include"input_state.h"
#include"input_interface.h"

const int kMaxKeyNum = 256;
const int kMaxPadButtonNum = 3;

struct InputState;

class PC : public IInput
{
public:

	PC();

	~PC() override;

	void Init();

	/// @brief デバッグ用
	void Debug();

	/// @brief 更新
	void Update() override;

	/// @brief どのくらい入力されているかを時間で返す(key)
	/// @param key_code 
	/// @return 時間(秒)
	float GetPushingTimeKey(int key_code);

	/// <summary>
	/// マウスがどれくらい入力されているかを返す
	/// </summary>
	/// <returns>時間(秒)</returns>
	float GetPushingTimeMouseButton(int mouse_code);

	/// @brief どのくらいそのキーを離しているかを時間で返す
	/// @param key_code 
	/// @return 時間(秒)
	float GetReleaseTimeKey(int key_code);

	/// @brief どのくらいそのマウスボタンを離しているかを時間で返す
	/// @param mouse_code 
	/// @return 時間(秒)
	float GetReleaseTimeMouseButton(int mouse_code);

	/// @brief 現在入力されている回転量を返す
	/// @return mouse_wheel_rot_
	float GetMouseWheelRot();

	/// @brief マウスのposを返す
	/// @return mouse_pos_
	const VECTOR GetMousePos()const;

	const VECTOR GetMouseVel() const;

	const VECTOR GetMouseDir()const;

private:

	InputState key_state_[kMaxKeyNum];		// キーのpush状態
	InputState mouse_state_[kMaxPadButtonNum];	// マウスのpush状態

	VECTOR mouse_pos_;			// マウスのpos
	VECTOR mouse_vel_;
	VECTOR mouse_dir_;
	float mouse_wheel_rot_;		// ホイールの回転量

	/// <summary>
	/// キーのアップデート
	/// </summary>
	void UpdateKey();

	/// @brief マウスボタンのアップデート
	void UpdateMouseButton();

	/// @brief マウスのposアップデート
	void UpdateMousePos();

	/// @brief マウスホイールのアップデート
	void UpdateMouseWheel();

	/// @brief 引数を受け取りどのボタンかを認識し、それを返す
	/// @param mouse_num マウスの番号
	/// @return dxlibに元々ある変数にする
	int GetMouseButtonNum(int mouse_num);

};