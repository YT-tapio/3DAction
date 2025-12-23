#include<iostream>
#include<memory>
#include"DxLib.h"
#include"rigid_body.h"
#include"object_base.h"
#include"collider_base.h"
#include"vector_assistant.h"
#include"hit_interface.h"

RigidBody::RigidBody(std::shared_ptr<ColliderBase> coll, VECTOR* pos)
{
	pos_ = pos;
	vel_ = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	coll_ = coll;
}

RigidBody::~RigidBody()
{

}

void RigidBody::Init(std::weak_ptr<IHit> object)
{
	object_ = object;
}

void RigidBody::Update(const VECTOR& vel, const VECTOR& dir)
{
	vel_ = vel;
	dir_ = dir;
}

void RigidBody::OnHit(std::shared_ptr<IHit> object)
{
	if (auto o = object_.lock()) 
	{
		o->OnHit(object);
	}
}

std::shared_ptr<ColliderBase> RigidBody::GetCollider()
{
	return coll_;
}

std::shared_ptr<IHit> RigidBody::GetIHitObject()
{
	auto obj = object_.lock();
	return obj;
}
