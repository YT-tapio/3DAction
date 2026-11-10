#pragma once
#include"behavior_interface.h"

/// <summary>
/// target以上のスタミナがあるかを確認する
/// </summary>
class CheckStamina : public IBehavior
{
public:

	CheckStamina(float* current_stamina,const float target_stamina);

	~CheckStamina() override;

	BehaviorStatus Update() override;

private:

	float target_stamina_;
	float current_stamina_;
};
