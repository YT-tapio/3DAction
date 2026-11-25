#include<memory>
#include<functional>
#include"DxLib.h"
#include"faction.h"
#include"target_selector.h"
#include"check_inside_target.h"
#include"attack_target_interface.h"

CheckInsideTarget::CheckInsideTarget(std::weak_ptr<TargetSelector> target_selector,std::function<VECTOR()> get_owner_pos,const float& dist)
	: target_selector_(target_selector)
	, get_owner_pos_(get_owner_pos)
	, dist_(dist)
{

}

CheckInsideTarget::~CheckInsideTarget()
{

}

void CheckInsideTarget::Init()
{

}

void CheckInsideTarget::Entry()
{

}

BehaviorStatus CheckInsideTarget::Update()
{
	// 敵がいるかの確認を行い敵がいるならコンプリートを返す
	auto target_selector = target_selector_.lock();
	if (target_selector == nullptr) { return BehaviorStatus::kFailure; }
	auto target_info = target_selector->GetAttackTarget()->GetAttackTargetInfo();
	if (target_info.is_alive) { return BehaviorStatus::kFailure; }
	auto owner_pos = get_owner_pos_();
	auto target_pos = target_info.pos;
	auto owner_target_dist = VSub(target_pos, owner_pos);
	auto state = VSize(owner_target_dist) < dist_ ? BehaviorStatus::kComplete : BehaviorStatus::kFailure;

	return BehaviorStatus::kFailure;
}

void CheckInsideTarget::Exit()
{

}