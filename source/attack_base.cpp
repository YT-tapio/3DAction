#include<memory>
#include"attack_base.h"
#include"object_base.h"
#include"physics.h"

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

void AttackBase::Update()
{

}

void AttackBase::Debug()
{

}

void AttackBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}