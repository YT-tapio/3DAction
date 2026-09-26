#pragma once
#include"behavior_base.h"

class CheckHp : public BehaviorBase
{
public:

	CheckHp(std::shared_ptr<ObjectBase> owner, float* hp);

	~CheckHp() override;

	BehaviorStatus Update() override;

private:

	float* hp_;


};
