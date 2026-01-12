#include<iostream>
#include<memory>
#include"DxLib.h"
#include"rigid_body.h"
#include"object_base.h"
#include"collider_base.h"
#include"vector_assistant.h"
#include"physics_interface.h"

RigidBody::RigidBody(std::shared_ptr<ColliderBase> coll, std::shared_ptr<ColliderBase> foot_coll,VECTOR* pos,bool gravity, bool kinematic,float mass)
{
	pos_		= pos;
	vel_		= VectorAssistant::VGetZero();
	dir_		= VectorAssistant::VGetZero();
	before_vel_ = VectorAssistant::VGetZero();
	coll_ = coll;
	foot_coll_ = foot_coll;
	use_gravity_ = gravity;
	is_kinematic_ = kinematic;
	mass_ = mass;
}

RigidBody::~RigidBody()
{

}

void RigidBody::Init(std::weak_ptr<IPhysicsEventReceiver> object)
{
	object_ = object;
}

void RigidBody::Update(const VECTOR& vel)
{
	vel_ = vel;
	dir_ = VNorm(vel);
}

void RigidBody::SetPos()
{
	*pos_ = VAdd(*pos_, vel_);
}

void RigidBody::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	if (auto obj = object_.lock()) 
	{
		obj->OnHit(object);
	}
}

const VECTOR RigidBody::GetPosition() const
{
	return *pos_;
}

const VECTOR RigidBody::GetVelocity() const
{
	return vel_;
}

const VECTOR RigidBody::GetBeforeVelocity() const
{
	return before_vel_;
}

const bool RigidBody::IsMove() const
{
	// åªç›Ç‡ëOÇ‡ìÆÇ¢ÇƒÇ¢Ç»Ç¢Ç∆Ç´ÇÕ
	if (VSize(vel_) == 0.f) { return TRUE; }
	if (VSize(before_vel_) == 0.f) { return TRUE; }
	return FALSE;
}

const bool RigidBody::GetUseGravity() const
{
	return use_gravity_;
}

const bool RigidBody::GetIsKinematic() const
{
	return is_kinematic_;
}

std::shared_ptr<ColliderBase> RigidBody::GetCollider()
{
	return coll_;
}

std::shared_ptr<ColliderBase> RigidBody::GetFootCollider()
{
	return foot_coll_;
}

std::shared_ptr<IPhysicsEventReceiver> RigidBody::GetIPhysicsObject()
{
	auto obj = object_.lock();
	return obj;
}
