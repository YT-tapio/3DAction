#pragma once
#include"behavior_interface.h"

class CheckStamina : public IBehavior
{
public:

	CheckStamina(float* current_stamina);

	~CheckStamina() override;

private:

	float current_stamina_;
};
