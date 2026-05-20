#include<memory>
#include<string>
#include"behavior_base.h"
#include"character_behavior.h"
#include"behavior_status.h""
#include"character_base.h"

CharacterBehavior::CharacterBehavior(std::weak_ptr<CharacterBase> owner)
	:BehaviorBase(owner)
	,my_owner_(owner)
{

}

CharacterBehavior::~CharacterBehavior()
{

}

void CharacterBehavior::Init()
{

}

void CharacterBehavior::Entry()
{

}

BehaviorStatus CharacterBehavior::Update()
{
	return BehaviorStatus::kFailure;
}

void CharacterBehavior::Exit()
{

}

void CharacterBehavior::Draw()
{

}

void CharacterBehavior::Debug()
{

}