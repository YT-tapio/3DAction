#pragma once
#include"behavior_interface.h"

class CheckHp : public IBehavior
{
public:

	CheckHp(float* hp);

	~CheckHp() override;

	BehaviorStatus Update() override;

private:

	float* hp_;


};
