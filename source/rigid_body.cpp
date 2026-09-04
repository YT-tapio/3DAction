#include<string>
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
#include"condition_timer.h"
#include"variable_timer.h"

RigidBody::RigidBody(std::shared_ptr<ColliderBase> coll,VECTOR* pos,bool gravity, bool kinematic,float mass,float friction)
	: pos_(pos)
	, vel_(VectorAssistant::VGetZero())
	, dir_(VectorAssistant::VGetZero())
	, target_vel_(VectorAssistant::VGetZero())
	, coll_(coll)
	, use_gravity_(gravity)
	, is_kinematic_(kinematic)
	, mass_(mass)
	, friction_(friction)
	, fall_speed_(0.f)
	, is_active_(TRUE)
	, is_object_(FALSE)
	, on_ground_(FALSE)
	, is_landing_(FALSE)
	, is_stop_(FALSE)
	, tag_("Nothing")
	, tag_first_change_(FALSE)
	, stop_timer_(std::make_shared<VariableTimer>(0.f))
{
	
}

RigidBody::~RigidBody()
{
	printfDx("RigidBody Destroy\n");
}

void RigidBody::Init(std::weak_ptr<IPhysicsEventReceiver> object)
{
	object_ = object;
	// objectを変換する
	auto obj = std::dynamic_pointer_cast<ObjectBase>(object_.lock());
	is_object_ = obj != nullptr;
	
	vel_ = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	target_vel_ = VectorAssistant::VGetZero();
	fall_speed_ = 0.f;
	// is_active_ = TRUE;
	//is_object_ = FALSE;
	on_ground_ = FALSE;
	is_landing_ = FALSE;
	is_stop_ = FALSE;
	tag_ = "Nothing";
	tag_first_change_ = FALSE;
	tag_ = "Nothing";
}

void RigidBody::ResetVelocity()
{
	target_vel_	= VectorAssistant::VGetZero();
	vel_				= VectorAssistant::VGetZero();
}

void RigidBody::SetVelocity(const VECTOR& vel)
{
	if (is_stop_) { return; }
	vel_ = vel;
	dir_ = VNorm(vel_);
}

void RigidBody::SetTargetVelocity(const VECTOR& vel)
{
	target_vel_ = vel;
}

void RigidBody::SetTag(std::string tag)
{
	if (!tag_first_change_)
	{
		tag_ = tag;
		tag_first_change_ = TRUE;
	}
}

void RigidBody::Active()
{
	is_active_ = TRUE;
}

void RigidBody::NotActive()
{
	is_active_ = FALSE;
}

void RigidBody::Update()
{
	if (is_stop_)
	{
		// is_stopのタイマーの更新を行う
		stop_timer_->Update();
		if (stop_timer_->GetIsEnd())
		{
			is_stop_ = FALSE;
		}
	}
}

void RigidBody::UpdateVelocity(const VECTOR& vel)
{
	if (is_stop_) { return; }
	vel_ = vel;
	dir_ = VNorm(vel);
}

void RigidBody::AddForce()
{
	if (!use_gravity_) { return; }
	if (is_stop_) { return; }
	// 重力処理
	if (!on_ground_)
	{
		//if (fall_speed_ == 5.f) { printfDx("aa"); }
		fall_speed_ -= mass_ * FPS::GetInstance().GetDeltaTime() * 60.f;
		target_vel_ = VAdd(target_vel_, VGet(0.f, fall_speed_, 0.f));
	}
}


void RigidBody::SetPos()
{
	// もしstopなら更新しない
	if (is_stop_)
	{
		//printfDx("x:%.2f y:%.2f z:%.2f\n", vel_.x, vel_.y, vel_.z);
		return;
	}
	
	if (VSize(vel_) > 0.f)
	{
		*pos_ = VAdd(*pos_, vel_);
	}
}

void RigidBody::SetUpSpeed(float speed)
{
	fall_speed_ = speed;
	target_vel_.y = fall_speed_;
}

void RigidBody::CanMove()
{
	is_stop_ = FALSE;
}

void RigidBody::SetStop(const float& time)
{
	// もし時間を設定していない場合は無限に止める
	is_stop_ = TRUE;
	if (time == -1.f) { return; }
	stop_timer_->Stop();
	stop_timer_->ChangeMaxTime(time);
	stop_timer_->ReStart();
}

void RigidBody::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	if (auto obj = object_.lock())
	{
		obj->OnCollisionEnter(object);
	}
}

void RigidBody::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{
	if (auto obj = object_.lock())
	{
		obj->OnCollisionStay(object);
	}
}

void RigidBody::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	if (auto obj = object_.lock())
	{
		obj->OnCollisionExit(object);
	}
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
	if (object->GetRigidBody()->GetTag() == "player") { printfDx("プレイヤー\n"); }
	if (object->GetRigidBody()->GetTag() != "stage") 
	{ 
		return;
	}
	if (auto obj = object_.lock())
	{
		object_.lock()->OnGround(object);
	}

	// 着地の瞬間を記憶
	if (!on_ground_)
	{
		is_landing_ = TRUE;
		
		//printfDx("着地\n");
	}
	else
	{
		is_landing_ = FALSE;
	}
	fall_speed_ = 0.f;
	target_vel_.y = 0.f;
	vel_.y = 0.f;
	on_ground_ = TRUE;
	
}

void RigidBody::UnGround()
{
	if (auto obj = object_.lock())
	{
		object_.lock()->UnGround();
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

const float RigidBody::GetOwnerDeltaTime() const
{
	if (auto obj = object_.lock())
	{
		return obj->GetDeltaTime();
	}
	return 1.f;
}

const VECTOR RigidBody::GetPosition() const
{
	return *pos_;
}

const VECTOR RigidBody::GetVelocity() const
{
	return vel_;
}

const VECTOR RigidBody::GetTargetVelocity() const
{
	return target_vel_;
}

const bool RigidBody::IsMove() const
{
	// 現在も前も動いていないときは
	if (VSize(VectorAssistant::VGetFlat(vel_)) != 0.f) { return TRUE; }
	return FALSE;
}

const bool RigidBody::IsStop() const
{
	return is_stop_;
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

const bool RigidBody::CheckSameOwner(std::shared_ptr<IPhysicsEventReceiver> other_object) const
{
	return object_.lock() == other_object;
}

const std::string RigidBody::GetTag() const
{
	return tag_;
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
