#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<unordered_map>
#include<vector>
#include<memory>
#include"DxLib.h"
#include"object_base.h"
#include"player.h"
#include"area_heal_skill.h"
#include"area_heal_give_player.h"
#include"check_my_area.h"
#include"sphere.h"
#include"vector_assistant.h"
#include"input_base.h"

AreaHealSkill::AreaHealSkill(std::weak_ptr<Player> owner, VECTOR* pos,const float radius)
	: SkillBase(owner,std::make_shared<AreaHealGivePlayer>(owner,
		std::make_shared<CheckMyArea>(std::make_shared<Sphere>(radius,VectorAssistant::VGetZero()),pos ), pos))
{

}

AreaHealSkill::~AreaHealSkill()
{

}

void AreaHealSkill::Init()
{
	behavior_->Init();
}

void AreaHealSkill::Update()
{
	if (!CheckMyOwner()) { return; }
	auto owner = owner_.lock();

	// player‚É•ÏŠ·‚Å‚«‚é‚©
	if (owner == nullptr)
	{
		printfDx("playerˆÈŠO‚É‚Ískill‚ð“K‰ž‚Å‚«‚Ü‚¹‚ñ\n");
		return;
	}

	//
	if (CheckIsAreaHeal(owner))
	{
		//printfDx("”­“®\n");
	}


}

void AreaHealSkill::Draw()
{
	if (!CheckMyOwner()) { return; }


}

void AreaHealSkill::Debug()
{

}

bool AreaHealSkill::CheckIsAreaHeal(std::shared_ptr<Player> owner)
{
	if (owner->GetIsStop())							{ return FALSE; }
	if (!owner->GetInput()->IsStrongSkill())	{ return FALSE; }

	return TRUE;
}