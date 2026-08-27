#pragma once
#include"behavior_base.h"

class NoAnimJump : public BehaviorBase
{
public:

	NoAnimJump(std::weak_ptr<ObjectBase> owner,const float& up_speed);

	~NoAnimJump() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

protected:

	float up_speed_;


private:


};