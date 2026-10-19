#pragma once
#include<string>
#include<functional>
#include"stat_type.h"
#include"modifire_operation.h"

class IPlayerUIController
{
public:

	virtual ~IPlayerUIController() = default;

	virtual void MakeUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp, const std::string& name, const bool& is_main) = 0;

	virtual void MakeStaminaUI(std::function<float()> get_base_stamina, std::function<float()> get_current_stamina,
		std::function<bool()> can_use_stamina, std::function<float()> get_avoid_use_stamina_value, const std::string& name) = 0;

	virtual void SpawnStatModifire(std::function<bool()> end_condition, StatType stat_type, ModifireOperation operation, const std::string& character_name) = 0;

	virtual void MakeNormalSkillUI(int skill_id, std::function<bool()> can_use, std::function<float()> cool_time_ratio, const std::string& name) = 0;

	virtual void MakeStrongSkillUI(int skill_id, std::function<bool()> can_use, std::function<float()> cool_time_ratio, const std::string& name) = 0;

	virtual void ChangeIsMian(const bool& is_main, const std::string& name) = 0;

};