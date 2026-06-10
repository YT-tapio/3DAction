#pragma once

class HPBar;

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

private:

	PlayerUIGroup();

private:

	// ÉvÉåÉCÉÑÅ[Ç…ä÷Ç∑ÇÈuiÇΩÇø
	std::shared_ptr<HPBar> hp_ui_;

};