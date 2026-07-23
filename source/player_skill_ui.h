#pragma once
#include"skill_ui_data.h"

class PlayerSkillUI
{
public:

	PlayerSkillUI(const VECTOR& base_pos, const int font_handle, const int body_color, const int edge_color);

	~PlayerSkillUI();

	void Init();

	void Update();

	void Draw();

	void SetSkill(const SkillUIData& skill_data, std::function<float()> cool_time_ratio, std::function<bool()> can_use);
	
private:

	void LoadFile();

private:

	VECTOR pos_;

	std::function<float()> cool_time_ratio_;	// クールタイムの割合
	std::function<bool()> can_use_;				// スキルを使う子ができるか

	SkillUIData data_;
	
	int font_handle_;
	int body_color_;
	int edge_color_;

};