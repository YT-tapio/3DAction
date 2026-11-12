#pragma once
#include"behavior_interface.h"

class CheckNearTarget : public IBehavior
{
public:

	CheckNearTarget(std::function<VECTOR()> get_owner_pos, std::function<VECTOR()> get_target_pos, const float& near_dist);

	~CheckNearTarget() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	std::function<VECTOR()> get_owner_pos_;
	std::function<VECTOR()> get_target_pos_;

	float near_dist_;
};