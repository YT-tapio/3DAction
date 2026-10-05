#pragma once
#include"player_ui_group_interface.h"

class HPBar;
class StringUI;
class PlayerLastBackGroundUI;
class PlayerIconUI;
class Animator2D;
class IUIObject;
class StatModifireUIGroup;
class SubScreen;

class PlayerUIGroup : public IPlayerUIGroup
{
public:

	PlayerUIGroup(const VECTOR& offset,const bool& is_main);

	~PlayerUIGroup();

	void Init();

	void Update();

	void Draw();

	void MakeUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp, const std::string& name) override;

	void MakeStaminaUI(std::function<float()> get_base_stamina, std::function<float()> get_current_stamina,
		std::function<bool()> can_use_stamina, std::function<float()> get_avoid_use_stamina_value) override;

	void MakeNormalSkillUI(int skill_id, std::function<bool()> can_use, std::function<float()> cool_time_ratio) override;

	void MakeStrongSkillUI(int skill_id, std::function<bool()> can_use, std::function<float()> cool_time_ratio) override;

	void SpawnStatModifire(std::function<bool()> end_condition, StatType stat_type, ModifireOperation operation);

	void SetIsMain(const bool& is_main);

private:

	void UpdateSubScreen();

private:

	// ベースのポジションと大きさ
	std::shared_ptr<SubScreen> screen_;

	// プレイヤーに関するuiたち
	std::shared_ptr<HPBar> hpbar_;
	std::shared_ptr<StringUI> hp_actual_;	// 実数値
	std::shared_ptr<PlayerLastBackGroundUI> last_background_;
	std::shared_ptr<PlayerIconUI> icon_;
	std::shared_ptr<StringUI> player_name_;
	std::shared_ptr<IUIObject> stamina_ui_;
	std::shared_ptr<StatModifireUIGroup> stat_modifire_ui_group_;

	VECTOR offset_;

	bool is_main_;

};