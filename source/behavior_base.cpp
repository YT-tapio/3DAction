#include<memory>
#include"behavior_base.h"
#include"object_base.h"

BehaviorBase::BehaviorBase(std::weak_ptr<ObjectBase> owner)
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

void BehaviorBase::Exit()
{

}

void BehaviorBase::Draw()
{

}

void BehaviorBase::Debug()
{

}

std::weak_ptr<ObjectBase> BehaviorBase::GetOwner()
{
	return owner_;
}