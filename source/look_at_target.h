#pragma once
#include"behavior_base.h"

class VariableTimer;

/// <summary>
/// —lŽqŒ©‚ð‚·‚é‚æ‚¤‚ÈŠ´‚¶
/// </summary>
class LookAtTarget : public BehaviorBase
{
public:

	LookAtTarget(std::weak_ptr<ObjectBase> owner, const float time);

	~LookAtTarget() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	void LookTarget();

private:
	std::shared_ptr<VariableTimer> timer_;

	float base_time_;

};