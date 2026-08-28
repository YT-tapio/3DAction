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

JumpSkill::JumpSkill(std::weak_ptr<Player> owner, std::pair<float,float> timing,const float up_speed, float cool_time)
	: SkillBase(owner,std::make_shared<Jump>(owner,"jump", timing,up_speed), SkillType::kConstant, cool_time)
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

	switch (state_)
	{

	case JumpState::ready:
		// ジャンプボタンが入力されているか
		if (IsPush())
		{
			// されていたらジャンプ
			behavior_->Entry();
			state_ = JumpState::jump;
			//printfDx("push\n");
			// スタミナの減少かつスタミナを使えないように
			if (auto owner = owner_.lock())
			{
				owner->GetStatusContainer()->StaminaDown(2.f);
				owner->GetStatusContainer()->StopHealStamina();
			}
		}
		break;

	case JumpState::jump:

		auto behavior_state = behavior_->Update();
		if (auto owner = owner_.lock())
		{
			if (behavior_state == BehaviorStatus::kComplete)
			{
				state_ = JumpState::ready;
				//printfDx("おわり\n");
			}
		}
		break;
	}
}

const bool JumpSkill::IsPush() const
{
	auto owner = owner_.lock();
	if (!owner->GetStatusContainer()->CanUseStamina()) { return FALSE; }
	if (!owner->GetCanMove()) { return FALSE; }		// 動けるか
	if (owner->GetIsStop()) { return FALSE; }
	if (!owner->GetRigidBody()->GetOnGround()) { return FALSE; }	// 地上にいるか
	if (!owner->GetInput()->IsJump()) { return FALSE; }		//押されてるか
	
	return TRUE;
}
