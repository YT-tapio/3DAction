#pragma once
#include"character_base.h"
#include"physics_interface.h"

class RigidBody;
class Punch;
class BehaviorBase;

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

	virtual void OnGrounded(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnUnGrounded(std::shared_ptr<IPhysicsEventReceiver> object) override;

protected:

	std::shared_ptr<RigidBody> rigid_body_;
	std::shared_ptr<BehaviorBase> punch_;

	std::string my_name_;

	VECTOR right_hand_pos_;

	float fall_speed_;
	bool is_ground_;

	virtual void UpdateBone();

private:




};