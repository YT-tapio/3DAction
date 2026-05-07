#include<memory>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"behavior_base.h"
#include"jump.h"
#include"behavior_status.h"
#include"character_base.h"
#include"animator_base.h"
#include"physics_interface.h"
#include"rigid_body.h"

Jump::Jump(std::weak_ptr<ObjectBase> owner, std::string my_anim_name, float timing, float speed)
	: BehaviorBase(owner)
	, my_anim_name_(my_anim_name)
	, timing_(timing)
	, speed_(speed)
	, played_(FALSE)
{

}

Jump::~Jump()
{

}

void Jump::Init()
{

}

BehaviorStatus Jump::Update()
{
	// オーナーのアニメーターをもらう
	auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	if(character ==nullptr){ return BehaviorStatus::kFailure; }
	auto animator = character->GetAnimator();			// アニメーターを取得
	
	if (animator->GetRatio(my_anim_name_) < timing_) { played_ = FALSE; }
	// physics用に変換する
	auto physics_owner = std::dynamic_pointer_cast<IPhysicsEventReceiver>(character);
	auto owner_rigid_body = physics_owner->GetRigidBody();
	if (JumpCondition(animator,owner_rigid_body))
	{
		played_ = TRUE;
		owner_rigid_body->SetUpSpeed(speed_);
		return BehaviorStatus::kSuccess;
	}
	return BehaviorStatus::kFailure;
}

void Jump::Exit()
{

}

void Jump::Draw()
{

}

void Jump::Debug()
{

}


bool Jump::JumpCondition(std::shared_ptr<AnimatorBase> animator, std::shared_ptr<RigidBody> owner_rigid_body)
{
	if (played_) { return FALSE; }
	if (!owner_rigid_body->GetOnGround()) { return FALSE; }
	if (animator->GetRatio(my_anim_name_) < timing_) { return FALSE; }
	return TRUE;
}