#include<memory>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"attack_base.h"
#include"tackle.h"
#include"behavior_status.h"
#include"rigid_body.h"
#include"condition_timer.h"
#include"character_base.h"
#include"animator_base.h"

Tackle::Tackle(std::weak_ptr<ObjectBase> owner, std::shared_ptr<RigidBody> rigid_body, const float time)
	: AttackBase(owner,0.f,0.f)
	, activate_timer_(std::make_shared<ConditionTimer>(time))
{
	rigid_body_ = rigid_body;
}

Tackle::~Tackle()
{

}

void Tackle::Init()
{
	// rigid_bodyの登録
	rigid_body_->Init(weak_from_this());
	activate_timer_->Init();
}

void Tackle::Entry()
{
	// おーなーのアニメーションを流す
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
}

BehaviorStatus Tackle::Update()
{
	// タックルのアニメーションをずっと流しておきたい



	return BehaviorStatus::kRunning;
}

void Tackle::Exit()
{

}

void Tackle::Debug()
{

}

void Tackle::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

