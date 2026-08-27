#include<memory>
#include"DxLib.h"
#include"object_base.h"
#include"jump_infite_attack.h"
#include"behavior_status.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"capsule.h"

JumpInfiteAttack::JumpInfiteAttack(std::weak_ptr<ObjectBase> owner, float min_coll_ratio, float max_coll_ratio, float damage)
	: AttackBase(owner,min_coll_ratio,max_coll_ratio,damage)
{
	//rigid_body_ = std::make_shared<RigidBody>(std::make_shared<ColliderBase>(), , )
}

JumpInfiteAttack::~JumpInfiteAttack()
{

}

void JumpInfiteAttack::Init()
{

}

void JumpInfiteAttack::Entry()
{

}

BehaviorStatus JumpInfiteAttack::Update()
{

	return BehaviorStatus::kComplete;
}

void JumpInfiteAttack::Exit()
{

}

void JumpInfiteAttack::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void JumpInfiteAttack::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void JumpInfiteAttack::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}