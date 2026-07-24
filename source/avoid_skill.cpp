#include<iostream>
#include<memory>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<vector>
#include"DxLib.h"
#include"avoid_skill.h"
#include"avoid.h"
#include"player.h"
#include"input_base.h"
#include"animator_base.h"
#include"FPS.h"
#include"vector_assistant.h"
#include"status.h"
#include"status_container.h"
#include"time.h"

AvoidSkill::AvoidSkill(std::weak_ptr<Player> owner,float speed,float stamina_consumption)
	: SkillBase(owner,std::make_shared<Avoid>(owner),SkillType::kConstant,0.f)
	, speed_(speed)
	, stamina_consumption_(stamina_consumption)
{

}

AvoidSkill::~AvoidSkill()
{

}

void AvoidSkill::Init()
{
	behavior_->Init();
}

void AvoidSkill::Update()
{
	if (!CheckMyOwner()) { return; }
	auto owner = owner_.lock();

	// playerに変換できるか
	if (owner == nullptr)
	{
		printfDx("player以外にはskillを適応できません\n");
		return;
	}
	
	if (is_active_)
	{
		if (owner->GetAnimator()->GetNowAnimName() != "avoid")
		{
			is_active_ = FALSE;
			owner->SetIsStop(FALSE);
		}
	}
	else
	{
		if (CheckIsAvoid(owner))
		{
			// スタミナを減らす
			owner->GetStatusContainer()->StaminaDown(stamina_consumption_);
			is_active_ = TRUE;
			owner->GetAnimator()->PlayRequest("avoid");
			owner->SetIsStop(TRUE);
			DecideVelocity(owner);
		}
	}

	// 回避のupdate
	behavior_->Update();
}

void AvoidSkill::Debug()
{
	behavior_->Debug();
}

bool AvoidSkill::CheckIsAvoid(std::shared_ptr<Player> owner)
{
	if (!owner->GetCanMove()) { return FALSE; }
	if (!owner->GetStatusContainer()->CanUseStamina()) { return FALSE; }
	if (!owner->GetInput()->IsAvoid()) { return FALSE; }
	if (!owner->GetOnGround())								{ return FALSE; }
	if (owner->GetAnimator()->GetNowAnimName() == "avoid")	{ return FALSE; }
	return TRUE;
}

void AvoidSkill::DecideVelocity(std::shared_ptr<Player> owner)
{
	// オーナーの回避の速度をきめる

	VECTOR input_dir = owner->GetInputDir();
	VECTOR velocity = VScale(input_dir, speed_ * owner->GetTime()->GetFPSRate());
	owner->ResetVelocity();
	owner->SetVelocity(velocity);
	owner->SetRotation(VGet(0.f, VectorAssistant::VGetTan(VectorAssistant::VGetReverce(input_dir)), 0.f));
	owner->SetDirection(input_dir);
}