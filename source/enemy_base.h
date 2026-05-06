#pragma once
#include"character_base.h"
#include"physics_interface.h"

class RigidBody;
class Punch;
class BehaviorBase;
class BehaviorTree;

class EnemyBase : public CharacterBase, public IPhysicsEventReceiver
{
public:

	EnemyBase(const VECTOR& pos);

	virtual ~EnemyBase() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void LateUpdate() override;

	virtual void Draw() override;

	virtual void Debug() override;

	virtual void OnHit(std::shared_ptr<IPhysicsEventReceiver> obj) override;

	virtual void OnGround(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void UnGround(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual const bool GetOnGround() const;

	std::shared_ptr<RigidBody> GetRigidBody() override;

protected:

	std::shared_ptr<RigidBody> rigid_body_;
	std::shared_ptr<BehaviorBase> test_behavior_;
	std::shared_ptr<BehaviorTree> behavior_tree_;

	std::string my_name_;

	VECTOR right_hand_pos_;

	VECTOR double_punch_coll_pos_;

	float fall_speed_;

	virtual void UpdateBone();

private:




};