#pragma once
#include"behavior_base.h"
#include"physics_interface.h"

class ObjectBase;
class RigidBody;

class AttackBase : public BehaviorBase , public IPhysicsEventReceiver
{
public:

	AttackBase(std::weak_ptr<IPhysicsEventReceiver> owner);

	~AttackBase() override;

	void Init() override;

	void Update() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

protected:

	std::shared_ptr<RigidBody> rigid_body_;

private:

	

};