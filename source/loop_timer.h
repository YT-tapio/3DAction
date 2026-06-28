#pragma once

class LoopTimer : public ConditionTimer
{
public:

	LoopTimer(const float& max_time);

	~LoopTimer() override;

	void Init() override;

	void Update() override;

private:


};