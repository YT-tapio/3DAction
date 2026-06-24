#pragma once

class HPBar;
class StringUI;

class EnemyUIGroup
{
public:

	static EnemyUIGroup& GetInstance()
	{
		static EnemyUIGroup instance;
		return instance;
	}

	EnemyUIGroup(const EnemyUIGroup&) = delete;
	EnemyUIGroup& operator = (const EnemyUIGroup&) = delete;

	void Init();

	void Update();

	void Draw();

	/// <summary>
	/// hp‚È‚Ç‚ÌÀ”’l‚Ì•`‰æ‚ÌˆË—Š
	/// </summary>
	void MakeStatusUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp,std::string name);

private:

	EnemyUIGroup();

private:

	std::shared_ptr<HPBar> hp_bar_;
	std::shared_ptr<StringUI> name_;

};