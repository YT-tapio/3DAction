#pragma once
#include"skill_type.h"
#include"player_group_interface.h"

class Player;
class IPlayerUIGroup;
class PlayerSkillUIGroup;
class EnemyBase;
class IPlayerObserver;
class IShadowCreater;
class IDamageUIGroup;

class PlayerGroup : public IPlayerGroup
{
public:

	PlayerGroup();

	~PlayerGroup();
	
	void AddPlayerObserver(IPlayerObserver* observer);

	void Awake(VECTOR* camera_dir, std::shared_ptr<IPlayerUIGroup> player_ui_group,std::shared_ptr<EnemyBase> enemy,std::shared_ptr<IShadowCreater> shadow_creater,std::shared_ptr<IDamageUIGroup> damage_ui_group);

	void Init(std::shared_ptr<PlayerSkillUIGroup> skill_ui_group);

	void Update();

	void End();

	void LateUpdate();

	void Stop();

	void Draw();

	void Debug();

	VECTOR* GetCurrentPlayerHeadPos() override;

	VECTOR* GetCurrentPlayerFrontDir() override;

	/// <summary>
	/// ˆø”‚Éˆê”Ô‹ß‚¢player‚ÌˆÊ’u‚ğ•Ô‚·
	/// </summary>
	/// <param name="pos">object‚Ìpos</param>
	/// <returns></returns>
	VECTOR MostNearPlayerPos(const VECTOR& pos) override;

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