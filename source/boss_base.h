#pragma once
#include"status_holder_interface.h"
#include"enemy_base.h"

class IShadowCreater;
class IEnemyUIGroup;
class IDamageUIGroup;
class IEnemyUIGroup;
class IAttackRangeGroup;

class BossBase : public EnemyBase
{
public:

	BossBase(const VECTOR& pos, bool* game_start,std::shared_ptr<IShadowCreater> shadow_creater, 
		std::shared_ptr<IEnemyUIGroup> enemy_ui_group, std::shared_ptr<IDamageUIGroup> damage_ui_group,
		std::shared_ptr<IPlayerGroup> player_group,std::shared_ptr<IAttackRangeGroup> attack_range_group);
	
	virtual ~BossBase() override;

	virtual void Init() override;

	virtual void Update() override;

protected:

	virtual void MakeBehaviorTree(std::shared_ptr<EnemyBase> mine) override;

	virtual void UpdatePhase();

	virtual void LoadFile() override;

	const bool IsBoss() const override;

private:


};
