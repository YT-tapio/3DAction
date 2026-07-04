#pragma once

class ConditionTimer;

///時間が可変のタイマー
class VariableTimer : public ConditionTimer
{
public:

	VariableTimer(float max_time = 0.f);

	~VariableTimer() override;

	/// <summary>
	/// タイマーが動いていないときのみチェンジ可能
	/// </summary>
	void ChangeMaxTime(float max_time);

private:




};

