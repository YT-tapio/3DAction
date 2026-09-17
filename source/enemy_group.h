#pragma once
#include"summonable_interface.h"

class EnemyBase;
class IShadowCreater;
class IEnemyUIGroup;
class IDamageUIGroup;
class IPlayerGroup;
class IAttackRangeGroup;

class EnemyGroup : public ISummonable
{
public:

	EnemyGroup(bool* game_start, std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IEnemyUIGroup> enemy_ui_group,
		std::shared_ptr<IDamageUIGroup> damage_ui_group,std::shared_ptr<IPlayerGroup> player_group, std::shared_ptr<IAttackRangeGroup> attack_range_group);

	~EnemyGroup() override;

	void Awake();

	void Init();

	void Update();

	void Draw();

	void Debug();

	void Summon(const VECTOR& pos) override;

	const bool GetIsActive() const;

private:

	void LoadFile();

private:

	std::vector<std::shared_ptr<EnemyBase>> enemies_;

	bool is_active_;
};