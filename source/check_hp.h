#pragma once
#include"behavior_interface.h"

class CheckHp : public IBehavior
{
public:

	CheckHp(float* hp,const float target_hp);

	~CheckHp() override;

	BehaviorStatus Update() override;

private:

	float target_hp_;
	float* hp_;


};
