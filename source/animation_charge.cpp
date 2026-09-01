#include<iostream>
#include<memory>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"behavior_base.h"
#include"animation_charge.h"
#include"object_base.h"
#include"behavior_status.h"
#include"character_base.h"
#include"animator_base.h"

AnimationCharge::AnimationCharge(std::weak_ptr<ObjectBase> owner, std::string my_anim_name, float timing_ratio)
	: BehaviorBase(owner)
	, my_anim_name_(my_anim_name)
	, timing_ratio_(timing_ratio)
{

}

AnimationCharge::~AnimationCharge()
{

}

void AnimationCharge::Init()
{

}

void AnimationCharge::Entry()
{
	printfDx("アニメーションチャージ\n");
	if (auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		character->GetAnimator()->PlayRequest(my_anim_name_);
	}
	else
	{
		printfDx("CharacterBase以外への適応できません\n");
	}
}

BehaviorStatus AnimationCharge::Update()
{
	// アニメーションのタイミングでコンプリートを返す。

	if (auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		if (character->GetAnimator()->GetRatio(my_anim_name_) > timing_ratio_) 
		{ 
			return BehaviorStatus::kComplete;
		}
	}
	else
	{
		printfDx("CharacterBase以外への適応できません\n");
	}

	return BehaviorStatus::kRunning;
}

void AnimationCharge::Exit()
{

}

void AnimationCharge::Debug()
{

}