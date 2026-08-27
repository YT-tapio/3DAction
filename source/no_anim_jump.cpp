#include<memory>
#include<utility>
#include"DxLib.h"
#include"object_base.h"
#include"no_anim_jump.h"
#include"behavior_status.h"
#include"physics_interface.h"
#include"rigid_body.h"

NoAnimJump::NoAnimJump(std::weak_ptr<ObjectBase> owner, const float& speed)
	: BehaviorBase(owner)
	, up_speed_(speed)
{

}

NoAnimJump::~NoAnimJump()
{

}

void NoAnimJump::Init()
{

}

void NoAnimJump::Entry()
{
	auto owner = owner_.lock();
	
	if (auto owner_physics = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner))
	{
		owner_physics->GetRigidBody()->SetUpSpeed(up_speed_);
	}
}

BehaviorStatus NoAnimJump::Update()
{
	return BehaviorStatus::kComplete;
}

void NoAnimJump::Exit()
{

}