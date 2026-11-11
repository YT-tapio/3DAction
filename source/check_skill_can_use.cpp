#include<functional>
#include"check_skill_can_use.h"

CheckSkillCanUse::CheckSkillCanUse(std::function<bool()> get_can_use)
	: IBehavior()
	, get_can_use_(get_can_use)
{

}

CheckSkillCanUse::~CheckSkillCanUse()
{

}

void CheckSkillCanUse::Init()
{

}

void CheckSkillCanUse::Entry()
{

}

BehaviorStatus CheckSkillCanUse::Update()
{
	if (get_can_use_ == nullptr) { return BehaviorStatus::kFailure; }

    auto can_use = get_can_use_();

	return can_use ? BehaviorStatus::kComplete : BehaviorStatus::kFailure;
}


void CheckSkillCanUse::Exit()
{

}