#include<memory>
#include<string>
#include"attack_base.h"
#include"object_base.h"
#include"physics.h"
#include"behavior_status.h"

AttackBase::AttackBase(std::weak_ptr<ObjectBase> owner, float min_coll_ratio, float max_coll_ratio, float damage_rate)
	: BehaviorBase(owner)
	, coll_timing_min_(min_coll_ratio)
	, coll_timing_max_(max_coll_ratio)
	, damage_rate_(damage_rate)
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

void AttackBase::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void AttackBase::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void AttackBase::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void AttackBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

std::shared_ptr<RigidBody> AttackBase::GetRigidBody()
{
	return rigid_body_;
}

bool AttackBase::CheckSameOwner(std::shared_ptr<ObjectBase> other_owner)
{
	auto owner = owner_.lock();
	return owner == other_owner;
}