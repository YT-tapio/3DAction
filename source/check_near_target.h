#pragma once
#include"behavior_interface.h"

class TargetSelector;

class CheckNearTarget : public IBehavior
{
public:

	CheckNearTarget(std::weak_ptr<TargetSelector> target_selector, std::function<VECTOR()> get_owner_pos, const float& near_dist);

	~CheckNearTarget() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	std::weak_ptr<TargetSelector> target_selector_;
	std::function<VECTOR()> get_owner_pos_;

	float near_dist_;
};