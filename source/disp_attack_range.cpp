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
#include"attack_range_group_interface.h"
#include<iostream>
DispAttackRange::DispAttackRange(std::weak_ptr<ObjectBase> owner, VECTOR* pos, const VECTOR& attack_range_scale, 
	std::function<bool()> end_function, const float& time, std::shared_ptr<IAttackRangeGroup> attack_range_group)
	: BehaviorBase(owner)
	, pos_(pos)
	, attack_range_scale_(attack_range_scale)
	, end_function_(end_function)
	, time_(time)
	, attack_range_group_(attack_range_group)
{

}

DispAttackRange::~DispAttackRange()
{
	std::cout << "dispAttackRange" << std::endl;
}

void DispAttackRange::Init()
{
	
}


void DispAttackRange::Entry()
{
	//printfDx("çUåÇîªíËÇÃï`âÊ");
	float ratio = 0.f;
	std::function<float()> get_ratio;
	if (auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		get_ratio = [owner]()
			{
				return owner->GetAnimator()->GetRatio("charge");
			};
	}

	VECTOR disp_pos = VAdd(*pos_, VGet(0.f, 0.1f, 0.f));
	disp_pos.y = -17.f;
	// ìñÇΩÇËîªíËÇÃï`âÊÇÉäÉNÉGÉXÉg
	//AttackRangeGroup::GetInstance().CircleDrawRequest(disp_pos,attack_range_scale_,time_, end_function_);
	attack_range_group_->CircleDrawRequest(disp_pos, attack_range_scale_, time_, end_function_);
}

BehaviorStatus DispAttackRange::Update()
{
	// ïKÇ∏ê¨å˜Çï‘Ç∑
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
