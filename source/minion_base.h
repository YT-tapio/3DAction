#pragma once
#include"enemy_base.h"

class IShadowCreater;

class MinionBase : public EnemyBase
{
public:

	MinionBase(const VECTOR& pos, bool* game_start, std::shared_ptr<IShadowCreater> shadow_creater,std::shared_ptr<IEnemyUIGroup> enemy_ui_group, std::shared_ptr<IDamageUIGroup> damage_ui_group,
		std::shared_ptr<IPlayerGroup> player_group, std::shared_ptr<IAttackRangeGroup> attack_range_group);

	virtual ~MinionBase() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void LateUpdate() override;

	virtual void Draw() override;

	virtual void Debug() override;

	virtual void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnGround(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void UnGround() override;

	//virtual void OnDamageFromPlayer(float damage, AttackType type) override;

protected:

	const bool IsBoss() const override;

private:


};