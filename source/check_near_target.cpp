#include<memory>
#include<functional>
#include"DxLib.h"
#include"check_near_target.h"
#include"faction.h"
#include"target_selector.h"
#include"attack_target_interface.h"

CheckNearTarget::CheckNearTarget(std::weak_ptr<TargetSelector> target_selector,std::function<VECTOR()> get_owner_pos, const float& near_dist)
	: IBehavior()
	, get_owner_pos_(get_owner_pos)
	, target_selector_(target_selector)
	, near_dist_(near_dist)
{

}

CheckNearTarget::~CheckNearTarget()
{

}

void CheckNearTarget::Init()
{

}

void CheckNearTarget::Entry()
{

}

BehaviorStatus CheckNearTarget::Update()
{
	auto target_selector = target_selector_.lock();
	if (target_selector == nullptr) { return BehaviorStatus::kFailure; }
	auto owner_pos = get_owner_pos_();
	auto target_pos = target_selector->GetAttackTarget()->GetAttackTargetInfo().pos;

	auto owner_target_dist = VSub(owner_pos, target_pos);
	auto state = VSize(owner_target_dist) < near_dist_ ? BehaviorStatus::kComplete : BehaviorStatus::kFailure;

	return state;
}

void CheckNearTarget::Exit()
{

}