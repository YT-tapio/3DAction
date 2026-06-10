#pragma once

class HPBar;
class HPActualValueUI;
class PlayerLastBackGroundUI;

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

	void MakeHPUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp);

	void End();

private:

	PlayerUIGroup();

private:

	// プレイヤーに関するuiたち
	std::shared_ptr<HPBar> hpbar_ui_;
	std::shared_ptr<HPActualValueUI> hp_actual_ui_;	// 実数値
	std::shared_ptr<PlayerLastBackGroundUI> last_background_;

};