#include<memory>
#include"DxLib.h"
#include"attack_base.h"
#include"stamp.h"
#include"object_base.h"
#include"behavior_status.h"
#include"capsule.h"
#include"sphere.h"
#include"physics.h"
#include"rigid_body.h"

Stamp::Stamp(std::weak_ptr<ObjectBase> owner, VECTOR* pos, float radius)
	: AttackBase(owner,0,0)
{
	//rigid_bodyを生成
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Sphere>(radius, VGet(0, 0, 0)), pos, FALSE, TRUE, 1.f, 1.f);
}

Stamp::~Stamp()
{

}

void Stamp::Init()
{
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
}

BehaviorStatus Stamp::Update()
{
	rigid_body_->NotActive();
	// オーナーが着地したら成功を返します。
	if (auto owner_physics = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner_.lock()))
	{
		auto owner_rigid_body = owner_physics->GetRigidBody();

		if (owner_rigid_body->GetIsLanding()) 
		{
			// この瞬間に当たり判定を発生する
			rigid_body_->Active();
			return BehaviorStatus::kSuccess;
		}
	}

	return BehaviorStatus::kRunning;
}

void Stamp::Debug()
{
	rigid_body_->Debug();
}

void Stamp::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}