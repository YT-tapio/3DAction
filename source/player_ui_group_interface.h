#pragma once
#include<string>
#include<functional>
#include"stat_type.h"
#include"modifire_operation.h"
class IPlayerUIGroup
{
public:

	virtual void MakeUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp, const std::string& name) {};

	virtual void MakeStaminaUI(std::function<float()> get_base_stamina, std::function<float()> get_current_stamina,
		std::function<bool()> can_use_stamina, std::function<float()> get_avoid_use_stamina_value) {};

	virtual void SpawnStatModifire(std::function<bool()> end_condition,StatType stat_type, ModifireOperation operation) {};
};