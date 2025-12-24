#include<iostream>
#include"DxLib.h"
#include"collider_base.h"


ColliderBase::ColliderBase(ColliderName name)
	:name_(name)
{

}

ColliderBase::~ColliderBase()
{

}

void ColliderBase::Draw(const VECTOR& pos)
{

}

const ColliderName ColliderBase::GetName() const
{
	return name_;
}