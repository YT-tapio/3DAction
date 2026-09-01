#pragma once
#include"enemy_ui_group_interface.h"

class HPBar;
class StringUI;

class EnemyUIGroup : public IEnemyUIGroup
{
public:

	EnemyUIGroup();

	~EnemyUIGroup();

	void Init();

	void Update();

	void Draw();

	/// <summary>
	/// hp‚È‚Ç‚ÌÀ”’l‚Ì•`‰æ‚ÌˆË—Š
	/// </summary>
	virtual void MakeStatusUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp,std::string name);

private:

	

private:

	std::shared_ptr<HPBar> hp_bar_;
	std::shared_ptr<StringUI> name_;

};