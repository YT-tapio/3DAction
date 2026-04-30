#include<memory>
#include"attack_base.h"
#include"object_base.h"
#include"physics.h"
#include"behavior_status.h"

AttackBase::AttackBase(std::weak_ptr<ObjectBase> owner, float min_coll_ratio, float max_coll_ratio)
	: BehaviorBase(owner)
	, min_coll_ratio_(min_coll_ratio)
	, max_coll_ratio_(max_coll_ratio)
{

}

AttackBase::~AttackBase()
{

}

void AttackBase::Init()
{

}

BehaviorStatus AttackBase::Update()
{
	return BehaviorStatus::kFailure;
}

void AttackBase::Debug()
{

}

void AttackBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}