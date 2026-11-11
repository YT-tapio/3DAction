#pragma once
#include"behavior_interface.h"

class CheckSkillCanUse : public IBehavior
{
public:

	CheckSkillCanUse(std::function<bool()> get_can_use);

	~CheckSkillCanUse() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;


private:

	std::function<float()> get_can_use_;

};