#pragma once
#include"character_base.h"
#include"physics_interface.h"

class RigidBody;

class EnemyBase : public CharacterBase, public IPhysicsEventReceiver
{
public:

	EnemyBase();

	virtual ~EnemyBase() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void LateUpdate() override;

	virtual void Draw() override;

	virtual void Debug() override;

	virtual void OnHit(std::shared_ptr<IPhysicsEventReceiver> obj) override;

	virtual void OnGrounded() override;

	virtual void OnUnGrounded() override;

protected:

	std::shared_ptr<RigidBody> rigid_body_;


	float fall_speed_;

	bool is_ground_;

private:




};