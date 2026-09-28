#pragma once
#include"behavior_interface.h"

class VariableTimer;

class CoolTimeBehavior : public IBehavior
{
public:

	CoolTimeBehavior(const float& time);

	~CoolTimeBehavior() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Draw() override;

	void Debug() override;

protected:

	std::shared_ptr<VariableTimer> timer_;
	float base_time_;

private:

	
};