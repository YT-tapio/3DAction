#pragma once
#include"enemy_controller_interface.h"
class EnemyBase;
class EnemyGroup;

class IShadowCreater;
class IEnemyUIGroup;
class IDamageUIGroup;
class IPlayerGroup;
class IAttackRangeGroup;
class IEnemyObserver;

class EnemyController : public IEnemyController
{
public:

	EnemyController(bool* game_start, std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IEnemyUIGroup> enemy_ui_group, std::shared_ptr<IDamageUIGroup> damage_ui_group,
		std::shared_ptr<IPlayerGroup> player_group, std::shared_ptr<IAttackRangeGroup> attack_range_group);

	~EnemyController();

	void Awake();

	void Init();

	void Update();

	void AddBossObserver(IEnemyObserver* observer) override;

	const void Draw() const;

	const VECTOR GetBossCenterPos() const override;

	const VECTOR GetBossFrontDir() const override;

private:

	// 
	std::shared_ptr<EnemyBase> boss_;
	std::vector<std::shared_ptr<EnemyGroup>> enemy_groups_;
	
};