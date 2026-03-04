
#include<iostream>
#include"DxLib.h"
#include"enemy_base.h"
#include"capsule.h"
#include"rigid_body.h"
#include"FPS.h"
#include"vector_assistant.h"
#include"debug.h"
#include"physics.h"
#include"object_setter.h"
#include"animator_base.h"

EnemyBase::EnemyBase()
	: CharacterBase("enemy")
	, IPhysicsEventReceiver()
{
	vel_ = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	pos_ = VGet(10.f, -2.f, 10.f);

	scale_ = VectorAssistant::VGetSame(0.05f);

	handle_ = MV1LoadModel("data/model/enemy/zako/Demon_T_Wiezzorek.mv1");
	if (handle_ == -1) { printfDx("ì«Ç›çûÇ›ÉGÉâÅ[\n"); }
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(1.5f, 6.f, VectorAssistant::VGetZero()), &pos_, TRUE, FALSE, 1.f);
	fall_speed_ = 0.f;
	is_ground_ = FALSE;

}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Init()
{
	rigid_body_->Init(weak_from_this());
	// physicsÇÃìoò^
	Physics::GetInstance().AddBody(rigid_body_);
	// setterÇ÷ÇÃìoò^
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
	auto mine = shared_from_this();
	//animator_ = std::make_shared<AnimatorEnemyBase>(handle_, std::dynamic_pointer_cast<EnemyBase>(mine));
}

void EnemyBase::Update()
{
	VECTOR dir = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	vel_ = dir;
	if (!is_ground_)
	{
		fall_speed_ += 0.03f;
		vel_ = VAdd(vel_, VGet(0.f, -fall_speed_, 0.f));
	}

	vel_ = VScale(vel_, (FPS::GetInstance().GetDeltaTime() * 60.f));
	rigid_body_->SetVelocity(vel_);
}

void EnemyBase::LateUpdate()
{

}

void EnemyBase::Draw()
{
	MV1DrawModel(handle_);
}

void EnemyBase::Debug()
{
	rigid_body_->Debug();
}

void EnemyBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> obj)
{
	
}

void EnemyBase::OnGrounded()
{
	is_ground_ = TRUE;
	fall_speed_ = 0.f;
}

void EnemyBase::OnUnGrounded()
{
	is_ground_ = FALSE;
}