#pragma once
#include"skill_type.h"

class Player;
class IPlayerUIGroup;
class PlayerSkillUIGroup;
class EnemyBase;
class IPlayerObserver;

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

	void AddPlayerObserver(IPlayerObserver* observer);

	void Awake(VECTOR* camera_dir, std::shared_ptr<IPlayerUIGroup> player_ui_group,std::shared_ptr<EnemyBase> enemy);

	void Init(std::shared_ptr<PlayerSkillUIGroup> skill_ui_group);

	void Update();

	void End();

	void LateUpdate();

	void Stop();

	void Draw();

	void Debug();

	VECTOR* GetCurrentPlayerHeadPos();

	VECTOR* GetCurrentPlayerFrontDir();

	/// <summary>
	/// ˆø”‚Éˆê”Ô‹ß‚¢player‚ÌˆÊ’u‚ğ•Ô‚·
	/// </summary>
	/// <param name="pos">object‚Ìpos</param>
	/// <returns></returns>
	VECTOR MostNearPlayerPos(const VECTOR& pos);

	/// <summary>
	/// Œ»İ‚ÌSkillID‚ğæ“¾
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	const int GetCurrentPlayerSkillID(SkillType type) const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	const float GetCurrentPlayerSkillCoolTime(SkillType type) const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	const bool GetCurrentPlayerSkillCanUse(SkillType type) const;

private:

	PlayerGroup();

	void CheckCurrentPlayerInfo();

private:

	std::vector<std::shared_ptr<Player>> players_;

	VECTOR current_player_head_pos_;
	VECTOR current_player_front_dir_;
	VECTOR* camera_dir_;

	int current_player_skill_id_;
	float current_player_skill_cool_time_;
	bool current_player_skill_can_use_;
};