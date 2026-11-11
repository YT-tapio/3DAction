#include"DxLib.h"
#include"execute_skill.h"

#include<vector>
#include<memory>
#include"input_base.h"
#include"ai_input.h"

ExecuteSkill::ExecuteSkill(AIInput* input,const SkillType& type)
	: IBehavior()
	, input_(input)
	, type_(type)
{

}

ExecuteSkill::~ExecuteSkill()
{

}

void ExecuteSkill::Init()
{

}

void ExecuteSkill::Entry()
{

}

BehaviorStatus ExecuteSkill::Update()
{
	if (input_ == nullptr) { return BehaviorStatus::kFailure; }

	input_->PushSkill(type_);

	return BehaviorStatus::kComplete;
}

void ExecuteSkill::Exit()
{

}