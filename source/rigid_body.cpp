#include<iostream>
#include<memory>
#include"DxLib.h"
#include"rigid_body.h"
#include"object_base.h"
#include"collider_base.h"
#include"vector_assistant.h"
#include"physics_interface.h"
#include"FPS.h"
#include"debug.h"
#include"color.h"

RigidBody::RigidBody(std::shared_ptr<ColliderBase> coll,VECTOR* pos,bool gravity, bool kinematic,float mass,float friction)
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
	friction_ = friction;
	fall_speed_ = 0.f;
	is_active_ = TRUE;
	is_object_ = FALSE;
	on_ground_ = FALSE;
	is_landing_ = FALSE;
}

RigidBody::~RigidBody()
{

}

void RigidBody::Init(std::weak_ptr<IPhysicsEventReceiver> object)
{
	object_ = object;
	// objectを変換する
	auto obj = std::dynamic_pointer_cast<ObjectBase>(object_.lock());
	is_object_ = obj != nullptr;
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
	if (!use_gravity_) { return; }
	// 重力処理
	if (!on_ground_)
	{
		if (fall_speed_ == 5.f) { printfDx("aa"); }
		fall_speed_ -= mass_ * FPS::GetInstance().GetDeltaTime() * 60.f;
		target_vel_ = VAdd(target_vel_, VGet(0.f, fall_speed_, 0.f));
	}
}

void RigidBody::ResetGravity()
{
	before_vel_.y = 0.f;
}

void RigidBody::SetPos()
{
	*pos_ = VAdd(*pos_, vel_);
}

void RigidBody::SetUpSpeed(float speed)
{
	fall_speed_ = speed;
	target_vel_.y = fall_speed_;
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

void RigidBody::OnGround(std::shared_ptr<IPhysicsEventReceiver> object)
{
	if (auto obj = object_.lock())
	{
		object_.lock()->OnGround(object);
	}

	// 着地の瞬間を記憶
	if (!on_ground_)
	{
		is_landing_ = TRUE;
	}
	else
	{
		is_landing_ = FALSE;
		printfDx("FALSE\n");
	}

	on_ground_ = TRUE;
	fall_speed_ = 0.f;
	target_vel_.y = 0.f;
	vel_.y = 0.f;
}

void RigidBody::UnGround(std::shared_ptr<IPhysicsEventReceiver> object)
{
	if (auto obj = object_.lock())
	{
		object_.lock()->UnGround(object);
	}

	on_ground_ = FALSE;
	is_landing_ = FALSE;
}

const void RigidBody::Debug() const
{
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "--RigidBody--", Color::kWhite);
	Debug::GetInstance().Add();

	if (!is_active_) { return; }
	VECTOR segment_start_pos = VAdd(*pos_, VGet(0.f, 0.f, 0.f));
	VECTOR segment_end_pos = VAdd(*pos_, VGet(0.f, -0.5f, 0.f));
	DrawLine3D(segment_start_pos, segment_end_pos, GetColor(0, 255, 255));
	coll_->Draw(*pos_);

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "vel", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(vel_);
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "target_vel", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(target_vel_);
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "fall_speed : %.2f", fall_speed_);
	Debug::GetInstance().Add();
	if (on_ground_)
	{
		DrawString(0, Debug::GetInstance().GetNowLineSize(), "着地", Color::kWhite);
	}
	else
	{
		DrawString(0, Debug::GetInstance().GetNowLineSize(), "着地じゃない", Color::kWhite);
	}
	Debug::GetInstance().Add();
}

const float RigidBody::GetMaxSpeed() const
{
	return kMaxSpeed * VSize(vel_);
}

const float RigidBody::GetFriction() const
{
	return friction_;
}

const float RigidBody::GetFallSpeed() const
{
	return fall_speed_;
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

const bool RigidBody::GetOnGround() const
{
	return on_ground_;
}

const bool RigidBody::GetIsLanding() const
{
	return is_landing_;
}

const bool RigidBody::IsObject() const
{
	return is_object_;
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
