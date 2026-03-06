#pragma once

#include"attack_base.h"

class ObjectBase;

class Punch : public AttackBase
{
public:

	Punch(std::weak_ptr<ObjectBase> owner,VECTOR* pos,std::shared_ptr<RigidBody> body);

	~Punch()override;

	void Init() override;

	void Update() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

private:

	VECTOR* pos_;

};