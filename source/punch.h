#pragma once

#include"attack_base.h"

class Punch : public AttackBase
{
public:

	Punch(std::weak_ptr<IPhysicsEventReceiver> owner,VECTOR* pos);

	~Punch()override;

	void Init() override;

	void Update() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

private:

	VECTOR* pos_;

};