#include<memory>
#include"DxLib.h"
#include"jump_infite_attack_skill.h"
#include"jump_infite_attack.h"
#include<unordered_map>
#include"animator_base.h"
#include"player.h"
#include"rigid_body.h"
#include"input_base.h"
#include"attack_correction.h"
#include"vector_assistant.h"

JumpInfiteAttackSkill::JumpInfiteAttackSkill(std::weak_ptr<Player> owner, SkillType type, float cool_time)
	: SkillBase(owner,std::make_shared<JumpInfiteAttack>(owner,0.38f,0.65f,3.4f), type, cool_time)
{

}

JumpInfiteAttackSkill::~JumpInfiteAttackSkill()
{

}

void JumpInfiteAttackSkill::Init()
{
	behavior_->Init();
}

void JumpInfiteAttackSkill::Update()
{
	auto owner = owner_.lock();
	
	if (is_active_)
	{
		behavior_->Update();
		if (owner->GetAnimator()->GetNowAnimName() != "jump_infite_attack")
		{
			owner->SetIsStop(FALSE);
			is_active_ = FALSE;
			behavior_->Exit();
		}
	}
	if (IsPush())
	{
		is_active_ = TRUE;
		behavior_->Entry();
		auto dir = owner->GetDirection();
		VECTOR vel = VectorAssistant::VGetZero();
		bool is_insite = AttackCorrection::GetInstance().ApproachTheNearestEnemy(owner, vel, 22.5f, 0.65f);
		owner->SetIsStop(TRUE);
	}
}

void JumpInfiteAttackSkill::Debug()
{
	behavior_->Debug();
}

bool JumpInfiteAttackSkill::IsPush()
{
	auto owner = owner_.lock();
	if (is_active_) { return FALSE; }
	if (owner->GetRigidBody()->GetOnGround()) { return FALSE; }	// ’…’n‚µ‚Ä‚¢‚È‚¢
	if (!PushMyType()) { return FALSE; }	// Ž©•ª‚É‘Î‰ž‚µ‚Ä‚¢‚éƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚Ä‚¢‚é‚©

	return TRUE;
}