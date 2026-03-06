#include<memory>
#include"DxLib.h"
#include"punch.h"
#include"vector_assistant.h"
#include"object_base.h"
#include"physics.h"
#include"rigid_body.h"
#include"capsule.h"
#include"debug.h"
#include"enemy_base.h"
#include"player.h"
#include"object_base.h"
#include"animator_base.h"
Punch::Punch(std::weak_ptr<ObjectBase> owner, VECTOR* pos,std::shared_ptr<RigidBody> body)
	: AttackBase(owner)
{
	pos_ = pos;
	rigid_body_ = body;
}

Punch::~Punch()
{

}

void Punch::Init()
{
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
	rigid_body_->NotActive();
}

void Punch::Update()
{
	// どうしよう
	// 正直今この中ではただ手に当たり判定を持たせているだけなんだよな
	// ownerにpunchを発生させたいよな
	rigid_body_->Active();
	auto chara = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	//chara->GetAnimator()->PlayRequest("punch");
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
	auto owner = owner_.lock();

	auto player_from_owner = std::dynamic_pointer_cast<Player>(owner);
	auto enemy_from_owner = std::dynamic_pointer_cast<EnemyBase>(owner);
	auto player = std::dynamic_pointer_cast<Player>(object);
	auto enemy = std::dynamic_pointer_cast<EnemyBase>(object);
	// if (player == player_from_owner) { printfDx("同じオーナーです\n"); return; }

	// if (enemy != nullptr) { printfDx("enemyがいるぞおい"); return; }
	// if (player != nullptr) { printfDx("playerがいるぞ\n"); return; }

}