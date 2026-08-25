#include<unordered_map>
#include<memory>
#include<functional>
#include<vector>
#include"DxLib.h"
#include"behavior_base.h"
#include"disp_attack_range.h"
#include"attack_range_group.h"
#include"behavior_status.h"
#include<string>
#include"character_base.h"
#include"animator_base.h"

DispAttackRange::DispAttackRange(std::weak_ptr<ObjectBase> owner, VECTOR* pos, const VECTOR& attack_range_scale, 
	std::function<bool()> end_function, const float& time)
	: BehaviorBase(owner)
	, pos_(pos)
	, attack_range_scale_(attack_range_scale)
	, end_function_(end_function)
	, time_(time)
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
	float ratio = 0.f;
	std::function<float()> get_ratio;
	if (auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		get_ratio = [owner]()
			{
				return owner->GetAnimator()->GetRatio("charge");
			};
	}
	// 当たり判定の描画をリクエスト
	AttackRangeGroup::GetInstance().CircleDrawRequest(VAdd(*pos_,VGet(0.f,0.1f,0.f)),attack_range_scale_,time_, end_function_);
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
