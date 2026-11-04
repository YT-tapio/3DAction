#pragma once

class ConditionTimer;
class Time;

class PopupUI
{
public:

	PopupUI();

	~PopupUI();

	void Init();

	void Update();

	const void Draw() const;

	/// <summary>
	/// 表示開始
	/// </summary>
	/// <param name="handle">画像</param>
	void Spawn(const VECTOR pos,int handle, const int& size = 1.f);

	const bool GetIsActive() const;

private:

	VECTOR RandomSpawnPos(const VECTOR& pos);

private:

	// 止まっている時間
	std::shared_ptr<ConditionTimer> stop_timer_;
	std::shared_ptr<Time> time_;

	VECTOR spawn_pos_;
	VECTOR pos_;

	int handle_;

	float size_;
	float default_up_speed_;	// 初期の上昇量
	float current_up_speed_;
	float out_up_speed_;		// 消える際の上昇値
	float alpha_value_; // 0～255

	bool is_jump_;
	bool is_active_;


};