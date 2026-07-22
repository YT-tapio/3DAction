#include<iostream>
#include<memory>
#include<vector>
#include"DxLib.h"
#include"player.h"
#include"behavior_base.h"
#include"skill_base.h"

SkillBase::SkillBase(std::weak_ptr<Player> owner,std::shared_ptr<BehaviorBase> behavior,float cool_time)
	: owner_(owner)
	, behavior_(behavior)
	, cool_time_(std::make_shared<ConditionTimer>(cool_time))
	, can_use_(TRUE)
{
	is_active_ = FALSE;
}

SkillBase::~SkillBase()
{

}

void SkillBase::Init()
{

}

void SkillBase::Update()
{

}

void SkillBase::Draw()
{

}

void SkillBase::Debug()
{

}

const float SkillBase::GetCoolTiemRatio() const
{
	return cool_time_->GetRatio();
}

const bool SkillBase::CanUseSkill() const
{
	return can_use_;
}

const bool SkillBase::CheckMyOwner() const
{
	return owner_.lock() != nullptr;
}