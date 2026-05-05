#include<fstream>
#include<sstream>
#include<unordered_map>
#include<memory>
#include<string>
#include"DxLib.h"
#include"attack_base.h"
#include"double_punch.h"
#include"behavior_status.h"
#include"rigid_body.h"
#include"capsule.h"
#include"vector_assistant.h"
#include"character_base.h"
#include"animator_base.h"
#include"physics.h"
#include"physics_interface.h"

DoublePunch::DoublePunch(std::weak_ptr<ObjectBase> owner, std::string my_anim_name,
	float min_coll_ratio, float max_coll_ratio,VECTOR* pos,float vertical,float radius)
	: AttackBase(owner,min_coll_ratio,max_coll_ratio)
	, my_anim_name_(my_anim_name)
	, pos_(pos)
{
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(radius,vertical,VectorAssistant::VGetZero()),
		pos_, FALSE, TRUE, 1.f, 0.2f);
}

DoublePunch::~DoublePunch()
{
	
}

void DoublePunch::Init()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->NotActive();

	Physics::GetInstance().AddBody(rigid_body_);

}

BehaviorStatus DoublePunch::Update()
{
	if (CheckCollActive())
	{
		rigid_body_->Active();
	}
	else
	{
		rigid_body_->NotActive();
	}
	return BehaviorStatus::kFailure;
}

void DoublePunch::Exit()
{

}

void DoublePunch::Draw()
{

}

void DoublePunch::Debug()
{
	rigid_body_->Debug();
}

void DoublePunch::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	
}

const bool DoublePunch::CheckCollActive() const
{
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	auto anim_play_ratio = owner->GetAnimator()->GetRatio(my_anim_name_);
	if (min_coll_ratio_ > anim_play_ratio) { return FALSE; }
	if (max_coll_ratio_ < anim_play_ratio) { return FALSE; }
	return TRUE;
}