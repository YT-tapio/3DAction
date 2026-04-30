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
#include"behavior_status.h"

Punch::Punch(std::weak_ptr<ObjectBase> owner, VECTOR* pos,
	std::string my_anim_name, float min_coll_ratio, float max_coll_ratio, std::shared_ptr<RigidBody> body)
	: AttackBase(owner, min_coll_ratio, max_coll_ratio)
	, my_anim_name_(my_anim_name)
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

BehaviorStatus Punch::Update()
{
	// どうしよう
	// 正直今この中ではただ手に当たり判定を持たせているだけなんだよな
	// ownerにpunchを発生させたいよな
	rigid_body_->NotActive();
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	
	if (owner == nullptr) { return BehaviorStatus::kFailure; }
	auto owner_animator = owner->GetAnimator();
	if (owner_animator == nullptr) { return BehaviorStatus::kFailure; }

	//TODO：おわりのタイミングになったらsuccessするように

	float punch_play_time = owner_animator->GetRatio(my_anim_name_);
	// 当たり判定をのactiveをします
	if (punch_play_time > min_coll_ratio_ && punch_play_time < max_coll_ratio_) { rigid_body_->Active(); }

	return BehaviorStatus::kRunning;
}

void Punch::Exit()
{
	rigid_body_->NotActive();
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
	if (player == player_from_owner) { return; }

	//if (enemy != nullptr) { printfDx("enemyがいるぞおい"); return; }
	// if (player != nullptr) { printfDx("playerがいるぞ\n"); return; }

}