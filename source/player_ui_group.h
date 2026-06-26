#pragma once

class HPBar;
class StringUI;
class PlayerLastBackGroundUI;
class PlayerIconUI;
class Animator2D;
class IUIObject;

class PlayerUIGroup
{
public:

	static PlayerUIGroup& GetInstance()
	{
		static PlayerUIGroup instance;
		return instance;
	}

	PlayerUIGroup(const PlayerUIGroup&) = delete;
	PlayerUIGroup& operator = (const PlayerUIGroup&) = delete;

	void Init();

	void Update();

	void Draw();

	void MakeHPUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp, const std::string& name);

	void MakeStaminaUI(std::function<float()> get_base_stamina, std::function<float()> get_current_stamina,
		std::function<bool()> can_use_stamina, std::function<float()> get_avoid_use_stamina_value);

	void End();

private:

	PlayerUIGroup();

private:

	// プレイヤーに関するuiたち
	std::shared_ptr<HPBar> hpbar_;
	std::shared_ptr<StringUI> hp_actual_;	// 実数値
	std::shared_ptr<PlayerLastBackGroundUI> last_background_;
	std::shared_ptr<PlayerIconUI> icon_;
	std::shared_ptr<StringUI> player_name_;
	std::shared_ptr<IUIObject> stamina_ui_;
};