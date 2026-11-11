#pragma once
#include"behavior_interface.h"



class CheckSkill : public IBehavior
{
public:

	CheckSkill();

	~CheckSkill() override;

	BehaviorStatus Update() override;

private:



};