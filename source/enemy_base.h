#pragma once
#include"character_base.h"
#include"physics_interface.h"
#include"takable_damage_player_interface.h"
#include"status_holder_interface.h"
#include"phase.h"

enum class AttackType;
class RigidBody;
class Punch;
class BehaviorBase;
class BehaviorTree;
class StatusContainer;
class HitRedBody;
class IEnemyObserver;
class EnemyCoolTimeController;
class IEnemyUIGroup;
class IDamageUIGroup;

class EnemyBase : public CharacterBase, public IPhysicsEventReceiver,public ITakableDamagePlayer,public IStatusHolder
{
public:

	EnemyBase(const VECTOR& pos,bool* game_start, std::shared_ptr<IEnemyUIGroup> enemy_ui_group,std::shared_ptr<IDamageUIGroup> damage_ui_group);

	virtual ~EnemyBase() override;

	void AddObserver(IEnemyObserver* observer);

	virtual void Init() override;

	virtual void Update() override;

	virtual void LateUpdate() override;

	virtual void Draw() override;

	virtual void Debug() override;

	virtual void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnGround(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void UnGround() override;

	virtual void OnDamageFromPlayer(float damage,AttackType type) override;

	virtual const bool GetOnGround() const;

	std::shared_ptr<StatusContainer> GetStatusContainer() override;

	std::shared_ptr<RigidBody> GetRigidBody() override;

	const float GetDeltaTime() const override;

	const VECTOR GetAttackTargetPos() const override;

	const VECTOR GetCenterPos() const override;

protected:

	virtual void LoadFile();

	virtual void UpdateBone();

	virtual void Death();

protected:

	std::vector<IEnemyObserver*> observers_;

	std::shared_ptr<RigidBody> rigid_body_;
	std::shared_ptr<BehaviorBase> test_behavior_;
	std::shared_ptr<BehaviorTree> behavior_tree_;
	std::shared_ptr<EnemyCoolTimeController> cool_time_;
	std::shared_ptr<StatusContainer> status_container_;
	std::shared_ptr<HitRedBody> hit_red_body_;	// ÉqÉbÉgéûê‘Ç≠Ç»ÇÈ
	std::shared_ptr<IEnemyUIGroup> enemy_ui_group_;
	std::shared_ptr<IDamageUIGroup> damage_ui_group_;

	std::string my_name_;

	VECTOR right_hand_pos_;
	VECTOR double_punch_coll_pos_;
	VECTOR target_player_pos_;
	VECTOR hips_pos_;
	VECTOR flat_hips_pos_;
	VECTOR disp_attack_flat_pos_;	// ínè„ìäâeÇµÇΩpos

	Phase phase_;

	float fall_speed_;

	bool* game_start_;

private:

};