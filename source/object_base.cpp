#include"object_base.h"
#include"vector_assistant.h"
#include"time.h"

ObjectBase::ObjectBase()
{
	time_ = std::make_shared<Time>();
	pos_ = VectorAssistant::VGetZero();
	rot_ = VectorAssistant::VGetZero();
	is_active_ = TRUE;
}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::Init()
{

}

void ObjectBase::Update()
{

}

void ObjectBase::LateUpdate()
{

}

void ObjectBase::Draw()
{
	
}

void ObjectBase::Debug()
{

}

std::shared_ptr<Time> ObjectBase::GetTime()
{
	return time_;
}

const bool ObjectBase::GetIsActive() const
{
	return is_active_;
}

const VECTOR ObjectBase::GetPosition() const
{
	return pos_;
}