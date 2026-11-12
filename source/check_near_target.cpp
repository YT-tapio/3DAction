#include<functional>
#include"DxLib.h"
#include"check_near_target.h"

CheckNearTarget::CheckNearTarget(std::function<VECTOR()> get_owner_pos, std::function<VECTOR()> get_target_pos, const float& near_dist)
	: IBehavior()
	, get_owner_pos_(get_owner_pos)
	, get_target_pos_(get_target_pos)
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
	// 
	auto owner_pos = get_owner_pos_();
	auto target_pos = get_target_pos_();

	auto owner_target_pos = VSub(owner_pos, target_pos);
	auto state = VSize(owner_target_pos) < near_dist_ ? BehaviorStatus::kComplete : BehaviorStatus::kFailure;

	return state;
}

void CheckNearTarget::Exit()
{

}