#include<memory>
#include"DxLib.h"
#include"punch.h"
#include"vector_assistant.h"
#include"object_base.h"
#include"physics.h"
#include"rigid_body.h"
#include"capsule.h"
#include"debug.h"

Punch::Punch(std::weak_ptr<IPhysicsEventReceiver> owner, VECTOR* pos)
	: AttackBase(owner)
{
	pos_ = pos;
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(1.5f, 6.f, VectorAssistant::VGetZero()), pos_, TRUE, FALSE, 1.f);
}

Punch::~Punch()
{

}

void Punch::Init()
{
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
}

void Punch::Update()
{

}

void Punch::Debug()
{
	rigid_body_->Debug();
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----AttackCollider----", GetColor(255, 255, 255));
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(*pos_);
}

void Punch::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}