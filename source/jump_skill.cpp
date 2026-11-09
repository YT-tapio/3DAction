#include<memory>
#include<string>
#include<vector>
#include"DxLib.h"
#include"object_base.h"
#include"character_base.h"
#include"player.h"
#include"behavior_base.h"
#include"jump_skill.h"
#include"character_behavior.h"
#include"jump.h"
#include"rigid_body.h"
#include"input_base.h"
#include"behavior_status.h"
#include"status.h"
#include"status_container.h"
#include"rigid_body.h"

JumpSkill::JumpSkill(std::weak_ptr<Player> owner, std::pair<float,float> timing,const float up_speed, float cool_time)
	: SkillBase(owner,std::make_shared<Jump>(owner,"jump", timing,up_speed), SkillType::kConstant, cool_time)
	, is_complete_(FALSE)
{
	state_ = JumpState::ready;
}

JumpSkill::~JumpSkill()
{

}

void JumpSkill::Init()
{

}

void JumpSkill::Update()
{
	auto owner = owner_.lock();
	if (owner == nullptr) { return; }
	can_use_ = owner->GetStatusContainer()->CanUseStamina();
	switch (state_)
	{
	case JumpState::ready:
		
		// ジャンプボタンが入力されているか
		if (IsPush())
		{
			// されていたらジャンプ
			behavior_->Entry();
			state_ = JumpState::jump;
			is_complete_ = FALSE;
			//printfDx("push\n");
			// スタミナの減少かつスタミナを使えないように
			owner->GetStatusContainer()->StaminaDown(2.f);
			can_use_ = FALSE;
		}
		break;

	case JumpState::jump:

		auto behavior_state = behavior_->Update();
		if (behavior_state == BehaviorStatus::kComplete) { is_complete_ = TRUE; }
		if (is_complete_ && owner->GetRigidBody()->GetOnGround())
		{
			state_ = JumpState::ready;
			can_use_ = owner->GetStatusContainer()->CanUseStamina();
			is_complete_ = FALSE;
		}
		break;
	}

}

const bool JumpSkill::IsPush() const
{
	auto owner = owner_.lock();
	if (!can_use_) { return FALSE; }
	if (!owner->GetStatusContainer()->CanUseStamina()) 
	{
		return FALSE;
	}
	if (!owner->GetCanMove()) { return FALSE; }		// 動けるか
	if (owner->GetIsStop()) { return FALSE; }
	if (!owner->GetRigidBody()->GetOnGround()) { return FALSE; }	// 地上にいるか
	if (!owner->GetInput()->IsJump()) { return FALSE; }		//押されてるか
	
	return TRUE;
}
