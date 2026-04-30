#pragma once

class ConditionTimer
{
public:

	ConditionTimer(float max_time);

	~ConditionTimer();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// タイマー更新
	/// </summary>
	void Update();

	/// <summary>
	/// stopさせる
	/// </summary>
	void Stop();

	/// <summary>
	/// 最初から始める
	/// </summary>
	void Start();

	/// <summary>
	/// 途中から始める
	/// </summary>
	void ReStart();

	/// <summary>
	/// is_stop_を返す
	/// </summary>
	/// <returns>タイマーストップを返す</returns>
	const bool GetIsStop() const;

	/// <summary>
	/// is_endを返す
	/// </summary>
	/// <returns>タイマーがマックスまで達しているか</returns>
	const bool GetIsEnd() const;

private:

	bool is_stop_;
	bool is_end_;
	float max_time_;
	float time_;

};