#include<iostream>
#include<memory>
#include<vector>
#include"DxLib.h"
#include"player.h"
#include"behavior_base.h"
#include"skill_base.h"

SkillBase::SkillBase(std::weak_ptr<Player> owner, std::shared_ptr<BehaviorBase> behavior)
	: owner_(owner)
	, behavior_(behavior)
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