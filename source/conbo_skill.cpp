#include<fstream>
#include<sstream>
#include<string>
#include<memory>
#include<unordered_map>
#include<vector>
#include"DxLib.h"
#include"conbo_skill.h"
#include"object_base.h"
#include"conbo_action.h"
#include"player.h"
#include"behavior_base.h"
//#include"animator_base.h"
#include"input_base.h"

ConboSkill::ConboSkill(std::weak_ptr<Player> owner,std::shared_ptr<BehaviorBase> behavior)
	: SkillBase(owner,behavior)
{

}

ConboSkill::~ConboSkill()
{
	
}

void ConboSkill::Init()
{
	behavior_->Init();
}

void ConboSkill::Update()
{
	// behaviorをconboに変換する必要がある
	auto conbo_action = std::dynamic_pointer_cast<ConboAction>(behavior_);
	if (conbo_action == nullptr) { return; }
	
	if (IsStartConboAction(conbo_action))
	{
		auto owner = owner_.lock();
		owner->GetAnimator();
	}

}

void ConboSkill::Draw()
{

}

void ConboSkill::Debug()
{

}

bool ConboSkill::IsStartConboAction(std::shared_ptr<ConboAction> conbo_action)
{
	auto owner = owner_.lock();
	
	if (is_active_)													{ return FALSE; }
	if (!owner->GetIsGround())								{ return FALSE; }
	if (owner->GetIsStop())									{ return FALSE; }
	if (!conbo_action->CheckNextConboReady())	{ return FALSE; }
	//inputの確認


	return TRUE;
}