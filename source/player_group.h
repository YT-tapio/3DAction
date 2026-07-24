#pragma once
#include"skill_type.h"

class Player;
class IPlayerUIGroup;

class PlayerGroup
{
public:

	static PlayerGroup& GetInstance()
	{
		static PlayerGroup instance;
		return instance;
	}

	PlayerGroup(const PlayerGroup&) = delete;
	PlayerGroup& operator = (const PlayerGroup&) = delete;

	void Awake(VECTOR* camera_dir, std::shared_ptr<IPlayerUIGroup> player_ui_group);

	void Init();

	void Update();

	void End();

	void LateUpdate();

	void Draw();

	void Debug();

	VECTOR* GetCurrentPlayerHeadPos();

	/// <summary>
	/// à¯êîÇ…àÍî‘ãﬂÇ¢playerÇÃà íuÇï‘Ç∑
	/// </summary>
	/// <param name="pos">objectÇÃpos</param>
	/// <returns></returns>
	VECTOR MostNearPlayerPos(const VECTOR& pos);

	const int GetCurrentPlayerSkillID(SkillType type) const;

	const float GetCurrentPlayerSkillCoolTime(SkillType type) const;

	const bool GetCurrentPlayerSkillCanUse(SkillType type) const;

private:

	PlayerGroup();

	void CheckCurrentPlayerHeadPos();

private:

	std::vector<std::shared_ptr<Player>> players_;

	VECTOR current_player_head_pos_;
	VECTOR* camera_dir_;
};