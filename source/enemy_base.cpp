
#include<iostream>
#include"DxLib.h"
#include"enemy_base.h"
#include"sphere.h"
#include"capsule.h"
#include"rigid_body.h"
#include"FPS.h"
#include"vector_assistant.h"
#include"debug.h"
#include"physics.h"
#include"object_setter.h"
#include"animator_base.h"
#include"animator_enemy.h"
#include"punch.h"


EnemyBase::EnemyBase()
	: CharacterBase("enemy")
	, IPhysicsEventReceiver()
{
	vel_ = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	pos_ = VGet(10.f, -2.f, 10.f);
	right_hand_pos_ = VectorAssistant::VGetZero();
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

	UpdateBone();
	punch_ = std::make_shared<Punch>(std::dynamic_pointer_cast<ObjectBase>(mine), &right_hand_pos_, 
		std::make_shared<RigidBody>(std::make_shared<Sphere>(1.5f, VGet(0.f, 0.f, 0.f)), &right_hand_pos_, FALSE, TRUE, 1.f));
	animator_ = std::make_shared<AnimatorEnemy>(handle_, std::dynamic_pointer_cast<EnemyBase>(mine));
	animator_->Init();
	punch_->Init();
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
	rigid_body_->SetTargetVelocity(vel_);
	animator_->Update();
	UpdateBone();
	punch_->Update();
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
	punch_->Debug();
}

void EnemyBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> obj)
{
	auto punch = std::dynamic_pointer_cast<Punch>(obj);

	if (punch != nullptr)
	{
		animator_->PlayRequest("on_damage");
		printfDx("Ç¢Çƒ\n");
	}

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

void EnemyBase::UpdateBone()
{
	int hand_bone_num = 0;
	const TCHAR* hand_bone_path = "mixamorig:RightHand";
	hand_bone_num = MV1SearchFrame(handle_, hand_bone_path);
	MATRIX hand_mat = MV1GetFrameLocalWorldMatrix(handle_, hand_bone_num);
	VECTOR right_hand_pos = VectorAssistant::VGetPositionFromMatrix(hand_mat);
	right_hand_pos_ = right_hand_pos;
}