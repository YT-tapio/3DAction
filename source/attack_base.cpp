#include<memory>
#include"attack_base.h"
#include"object_base.h"
#include"physics.h"
#include"behavior_status.h"

AttackBase::AttackBase(std::weak_ptr<ObjectBase> owner)
	: BehaviorBase(owner)
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