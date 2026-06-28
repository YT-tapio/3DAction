#pragma once

class ConditionTimer;

///可変式のタイマー
class VariableTimer : public ConditionTimer
{
public:

	VariableTimer(float max_time);

	~VariableTimer() override;

	/// <summary>
	/// タイマーが動いていないときのみチェンジ可能
	/// </summary>
	void ChangeMaxTime(float max_time);

private:




};

