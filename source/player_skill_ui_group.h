#pragma once
#include"player_skill_ui.h"

class SkillUIDatas;

class PlayerSkillUIGroup
{
public:

	PlayerSkillUIGroup();

	~PlayerSkillUIGroup();

	void Init();

	void Update();

	void Draw();

	/// <summary>
	/// キャラクターチェンジする際に呼び出す
	/// </summary>
	/// <param name="normal_skill_id"></param>
	/// <param name="normal_skill_cool_time_ratio"></param>
	/// <param name="normal_skill_can_use"></param>
	/// <param name="strong_skill_id"></param>
	/// <param name="strong_cool_time_ratio"></param>
	/// <param name="strong_skill_can_use"></param>
	void ChangeSkill(const int normal_skill_id,std::function<float()> normal_skill_cool_time_ratio,std::function<bool()> normal_skill_can_use
		,const int strong_skill_id, std::function<float()> strong_cool_time_ratio, std::function<bool()> strong_skill_can_use);

private:

	void LoadFile();

private:

	std::shared_ptr<PlayerSkillUI> normal_skill_ui_;
	std::shared_ptr<PlayerSkillUI> strong_skill_ui_;

	std::shared_ptr<SkillUIDatas> skill_ui_datas_;

	VECTOR normal_skill_pos_;
	VECTOR strong_skill_pos_;

	int normal_skill_input_handle_;
	int strong_skill_input_handle_;

	int font_handle_;
	int body_color_;
	int edge_color_;

};