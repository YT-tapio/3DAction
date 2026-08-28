#pragma once
#include"behavior_base.h"
#include"attack_base.h"

class JumpInfiteAttack : public AttackBase
{
public:

	JumpInfiteAttack(std::weak_ptr<ObjectBase> owner, float min_coll_ratio, float max_coll_ratio, float damage);

	~JumpInfiteAttack() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Debug() override;

	void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

    void OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object) override;

	void OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object) override;

private:

	VECTOR pos_;	//HŒ|”»’è‚ÌoŒ»êŠ


};