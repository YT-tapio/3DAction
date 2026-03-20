#include<iostream>
#include<memory>
#include"DxLib.h"
#include"player.h"
#include"behavior_base.h"
#include"skill_base.h"

SkillBase::SkillBase(std::weak_ptr<Player> owner, std::shared_ptr<BehaviorBase> behavior)
	: owner_(owner)
	, behavior_(behavior)
{

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