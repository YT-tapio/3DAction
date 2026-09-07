#include<string>
#include"DxLib.h"
#include"bullet.h"
#include"vector_assistant.h"

#include"physics.h"
#include"model_repository.h"
#include"object_setter.h"

#include"rigid_body.h"

#include"collider_base.h"
#include"sphere.h"

Bullet::Bullet()
	: Object3D("")
	, vel_(VectorAssistant::VGetZero())
	, dir_(VectorAssistant::VGetZero())
	, handle_(-1)
	, speed_(0.f)
{
	scale_ = VectorAssistant::VGetSame(1.f);
	auto collider = std::make_shared<Sphere>(1.f, VectorAssistant::VGetZero());
	rigid_body_ = std::make_shared<RigidBody>(collider, &pos_, FALSE, FALSE, 1.f, 0.2f);
	handle_ = ModelRepository::GetInstance().GetHandle("ball");
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
	is_active_ = FALSE;
}

Bullet::~Bullet()
{
	if (handle_ != -1)
	{
		MV1DeleteModel(handle_);
		handle_ = -1;
	}
}

void Bullet::Init()
{
	rigid_body_->NotActive();
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
	is_active_ = FALSE;
}

void Bullet::Update()
{
	if (!is_active_) { return; }
	rigid_body_->SetTargetVelocity(vel_);
}

void Bullet::Draw()
{
	if (!is_active_) { return; }
	MV1DrawModel(handle_);
}

void Bullet::Shot(const VECTOR& pos, const VECTOR& dir)
{
	pos_ = pos;
	dir_ = dir;
	is_active_ = TRUE;
	speed_ = 1.f;
	vel_ = VScale(dir_, speed_);
	rigid_body_->Active();
}

void Bullet::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto target_tag = object->GetRigidBody()->GetTag();
	if (!object->GetRigidBody()->IsObject()) { return; }
	is_active_ = FALSE;
	rigid_body_->NotActive();
}

std::shared_ptr<RigidBody> Bullet::GetRigidBody()
{
	return rigid_body_;
}