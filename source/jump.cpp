#include<memory>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<utility>
#include"behavior_base.h"
#include"character_behavior.h"
#include"jump.h"
#include"behavior_status.h"
#include"character_base.h"
#include"animator_base.h"
#include"physics_interface.h"
#include"rigid_body.h"

Jump::Jump(std::weak_ptr<CharacterBase> owner, std::string my_anim_name, 
	std::pair<float,float> timing, float speed)
	: CharacterBehavior(owner)
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
	played_ = FALSE;
}

void Jump::Entry()
{
	played_ = FALSE;
	// アニメーションの再生
	if (auto owner = my_owner_.lock())
	{
		owner->GetAnimator()->PlayRequest(my_anim_name_);
	}
	// printfDx("jump_entry\n");
}

BehaviorStatus Jump::Update()
{
	//printfDx("jump\n");
	// オーナーのアニメーターをもらう
	auto owner = my_owner_.lock();
	if(owner ==nullptr){ return BehaviorStatus::kFailure; }
	
	if (JumpCondition(owner))
	{
		
		if (auto owner_rigid_body = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner))
		{
			if (owner_rigid_body->GetRigidBody()->GetOnGround()) 
			{
				played_ = TRUE;
				owner_rigid_body->GetRigidBody()->SetUpSpeed(speed_);
				return BehaviorStatus::kComplete;
			}
		}
	}
	return BehaviorStatus::kRunning;
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


bool Jump::JumpCondition(std::shared_ptr<CharacterBase> owner)
{
	if (played_) { return FALSE; }
	auto anim_ratio = owner->GetAnimator()->GetRatio(my_anim_name_);
	if (anim_ratio < timing_.first) { return FALSE; }
	if (anim_ratio > timing_.second) { return FALSE; }
	return TRUE;
}