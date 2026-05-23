#include<memory>
#include<string>
#include"attack_base.h"
#include"object_base.h"
#include"physics.h"
#include"behavior_status.h"

AttackBase::AttackBase(std::weak_ptr<ObjectBase> owner, float min_coll_ratio, float max_coll_ratio)
	: BehaviorBase(owner)
	, coll_timing_min_(min_coll_ratio)
	, coll_timing_max_(max_coll_ratio)
{

}

AttackBase::~AttackBase()
{

}

void AttackBase::Entry()
{

}

void AttackBase::Init()
{

}

BehaviorStatus AttackBase::Update()
{
	return BehaviorStatus::kFailure;
}

void AttackBase::Exit()
{

}

void AttackBase::Debug()
{

}

void AttackBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

std::shared_ptr<RigidBody> AttackBase::GetRigidBody()
{
	return rigid_body_;
}