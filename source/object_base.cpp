#include<iostream>
#include"DxLib.h"
#include"object_base.h"
#include"vector_assistant.h"

ObjectBase::ObjectBase()
{
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

void ObjectBase::Draw()
{

}

void ObjectBase::Debug()
{

}

const bool ObjectBase::GetIsActive() const
{
	return is_active_;
}