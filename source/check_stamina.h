#pragma once
#include"behavior_interface.h"

/// <summary>
/// target以上のスタミナがあるかを確認する
/// </summary>
class CheckStamina : public IBehavior
{
public:

	CheckStamina(std::function<float()> get_current_stamina, const float target_stamina);

	~CheckStamina() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	std::function<float()> get_current_stamina_;
	float target_stamina_;
};
