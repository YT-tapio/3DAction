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
	// rigid_body‚Ì“o˜^
	rigid_body_->Init(weak_from_this());
	activate_timer_->Init();
}

void Tackle::Entry()
{
	
}

BehaviorStatus Tackle::Update()
{
	


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

