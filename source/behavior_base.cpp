#include<memory>
#include"behavior_base.h"
#include"object_base.h"

BehaviorBase::BehaviorBase(std::weak_ptr<IPhysicsEventReceiver> owner)
	:owner_(owner)
{

}

BehaviorBase::~BehaviorBase()
{

}

void BehaviorBase::Init()
{

}

void BehaviorBase::Update()
{

}

void BehaviorBase::Debug()
{

}