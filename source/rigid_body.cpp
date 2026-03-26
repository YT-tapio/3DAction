#include<iostream>
#include<memory>
#include"DxLib.h"
#include"rigid_body.h"
#include"object_base.h"
#include"collider_base.h"
#include"vector_assistant.h"
#include"physics_interface.h"
#include"FPS.h"

RigidBody::RigidBody(std::shared_ptr<ColliderBase> coll,VECTOR* pos,bool gravity, bool kinematic,float mass)
{
	pos_		= pos;
	vel_		= VectorAssistant::VGetZero();
	dir_		= VectorAssistant::VGetZero();
	before_vel_ = VectorAssistant::VGetZero();
	target_vel_ = VectorAssistant::VGetZero();
	coll_ = coll;
	use_gravity_ = gravity;
	is_kinematic_ = kinematic;
	mass_ = mass;
	is_active_ = TRUE;
}

RigidBody::~RigidBody()
{

}

void RigidBody::Init(std::weak_ptr<IPhysicsEventReceiver> object)
{
	object_ = object;
}

void RigidBody::ResetVelocity()
{
	target_vel_	= VectorAssistant::VGetZero();
	vel_				= VectorAssistant::VGetZero();
}

void RigidBody::SetVelocity(const VECTOR& vel)
{
	vel_ = vel;
	dir_ = VNorm(vel_);
}

void RigidBody::SetTargetVelocity(const VECTOR& vel)
{
	target_vel_ = vel;
}

void RigidBody::Active()
{
	is_active_ = TRUE;
}

void RigidBody::NotActive()
{
	is_active_ = FALSE;
}

void RigidBody::Update(const VECTOR& vel)
{
	before_vel_ = vel_;
	vel_ = vel;
	dir_ = VNorm(vel);
}

void RigidBody::AddForce()
{
	// 重力処理
	// 前回のも比べる
	// 重さ
	float gravity_speed = -((FPS::GetInstance().GetDeltaTime() * 60.f) * mass_);
	gravity_speed = (gravity_speed + before_vel_.y);
	vel_.y += (gravity_speed);
}

void RigidBody::ResetGravity()
{
	before_vel_.y = 0.f;
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

void RigidBody::UnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	if (auto obj = object_.lock())
	{
		obj->UnHit(object);
	}
}

const void RigidBody::Debug() const
{
	if (!is_active_) { return; }
	VECTOR segment_start_pos = VAdd(*pos_, VGet(0.f, 0.f, 0.f));
	VECTOR segment_end_pos = VAdd(*pos_, VGet(0.f, -0.5f, 0.f));
	DrawLine3D(segment_start_pos, segment_end_pos, GetColor(0, 255, 255));
	coll_->Draw(*pos_);
}

const float RigidBody::GetMaxSpeed() const
{
	return kMaxSpeed * VSize(vel_);
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

const VECTOR RigidBody::GetTargetVelocity() const
{
	return target_vel_;
}

const bool RigidBody::IsMove() const
{
	// 現在も前も動いていないときは
	if (VSize(VectorAssistant::VGetFlat(vel_))			!= 0.f) { return TRUE; }
	if (VSize(VectorAssistant::VGetFlat(before_vel_))	!= 0.f) { return TRUE; }
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


std::shared_ptr<IPhysicsEventReceiver> RigidBody::GetIPhysicsObject()
{
	auto obj = object_.lock();
	return obj;
}

const bool RigidBody::GetIsActive() const
{
	return is_active_;
}
