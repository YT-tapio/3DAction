#include<memory>
#include"behavior_base.h"
#include"object_base.h"

BehaviorBase::BehaviorBase(std::weak_ptr<ObjectBase> owner)
	:owner_(owner)
	,is_active_(FALSE)
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

void BehaviorBase::Active()
{
	is_active_ = TRUE;
}

std::weak_ptr<ObjectBase> BehaviorBase::GetOwner()
{
	return owner_;
}