#pragma once
#include"character_base.h"
#include"physics_interface.h"
#include"takable_damage_player_interface.h"
#include"status_holder_interface.h"

enum class AttackType;
class RigidBody;
class Punch;
class BehaviorBase;
class BehaviorTree;
class StatusContainer;

class EnemyBase : public CharacterBase, public IPhysicsEventReceiver,public ITakableDamagePlayer,public IStatusHolder
{
public:

	EnemyBase(const VECTOR& pos);

	virtual ~EnemyBase() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void LateUpdate() override;

	virtual void Draw() override;

	virtual void Draw2D() override;

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

	const VECTOR GetAttackTargetPos() const override;

protected:

	virtual void UpdateBone();

protected:

	std::shared_ptr<RigidBody> rigid_body_;
	std::shared_ptr<BehaviorBase> test_behavior_;
	std::shared_ptr<BehaviorTree> behavior_tree_;

	std::shared_ptr<StatusContainer> status_container_;

	std::string my_name_;

	VECTOR right_hand_pos_;
	VECTOR double_punch_coll_pos_;
	VECTOR target_player_pos_;

	float fall_speed_;


private:


};