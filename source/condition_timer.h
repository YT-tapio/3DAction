#pragma once

class ConditionTimer
{
public:

	ConditionTimer(float max_time);

	virtual ~ConditionTimer();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init();

	/// <summary>
	/// タイマー更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// stopさせる
	/// </summary>
	void Stop();

	/// <summary>
	/// 今の時間から始める
	/// </summary>
	void Start();

	/// <summary>
	/// 初めから
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

protected:

	bool is_stop_;
	bool is_end_;
	float max_time_;
	float time_;

private:

};