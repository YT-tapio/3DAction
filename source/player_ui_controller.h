#pragma once
#include"player_ui_controller_interface.h"
class PlayerUIGroup;

class PlayerUIController : public IPlayerUIController
{
public:

	PlayerUIController();

	~PlayerUIController() override;

	/// <summary>
	/// プレイヤーによって生成
	/// </summary>
	void MakeUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp, const std::string& name, const bool& is_main) override;

	void MakeStaminaUI(std::function<float()> get_base_stamina, std::function<float()> get_current_stamina,
		std::function<bool()> can_use_stamina, std::function<float()> get_avoid_use_stamina_value, const std::string& name);

	void MakeNormalSkillUI(int skill_id, std::function<bool()> can_use, std::function<float()> cool_time_ratio, const std::string& name) override;

	void MakeStrongSkillUI(int skill_id, std::function<bool()> can_use, std::function<float()> cool_time_ratio, const std::string& name) override;

	void MakeSkillUI(int normal_skill_id, std::function<bool()> normal_can_use, std::function<float()> normal_cool_time_ratio,
		int strong_skill_id, std::function<bool()> strong_can_use, std::function<float()> strong_cool_time_ratio,const std::string& name);

	void SpawnStatModifire(std::function<bool()> end_condition, StatType stat_type, ModifireOperation operation, const std::string& name) override;

	void Init();

	void Update();

	void Draw();

	void ChangeIsMian(const bool& is_main, const std::string& name) override;

private:

	const VECTOR kOffset = VGet(0.f,-200.f,0.f);

	// プレイヤーのステータスに関するUI
	std::unordered_map<std::string, std::shared_ptr<PlayerUIGroup>> player_ui_groups_;
};