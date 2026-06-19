#include<unordered_map>
#include<memory>
#include<functional>
#include<vector>
#include"DxLib.h"
#include"behavior_base.h"
#include"disp_attack_range.h"
#include"attack_range_group.h"
#include"behavior_status.h"

DispAttackRange::DispAttackRange(std::weak_ptr<ObjectBase> owner, VECTOR* pos, const VECTOR& attack_range_scale, std::function<bool()> end_function)
	: BehaviorBase(owner)
	, pos_(pos)
	, attack_range_scale_(attack_range_scale)
	, end_function_(end_function)
{

}

DispAttackRange::~DispAttackRange()
{

}

void DispAttackRange::Init()
{

}


void DispAttackRange::Entry()
{
	// 当たり判定の描画をリクエスト
	AttackRangeGroup::GetInstance().DrawRequest(VAdd(*pos_,VGet(0.f,0.1f,0.f)),attack_range_scale_,end_function_);
}

BehaviorStatus DispAttackRange::Update()
{
	// 必ず成功を返す
	return BehaviorStatus::kComplete;
}

void DispAttackRange::Exit()
{

}

void DispAttackRange::Draw()
{

}

void DispAttackRange::Debug()
{

}
