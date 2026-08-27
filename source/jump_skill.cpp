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
#include"no_anim_jump.h"
#include"rigid_body.h"
#include"input_base.h"

JumpSkill::JumpSkill(std::weak_ptr<Player> owner, const float up_speed, float cool_time)
	: SkillBase(owner,std::make_shared<NoAnimJump>(owner,up_speed),SkillType::kConstant,cool_time)
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
		}
		break;

	case JumpState::jump:

		behavior_->Update();
		if (auto owner = owner_.lock())
		{
			if (owner->GetRigidBody()->GetIsLanding())
			{
				state_ = JumpState::ready;
			}
		}
		break;

	}
}

const bool JumpSkill::IsPush() const
{
	auto owner = owner_.lock();
	if (!owner->GetCanMove()) { return FALSE; }		// 動けるか
	if (!owner->GetRigidBody()->GetOnGround()) { return FALSE; }	// 地上にいるか
	if (!owner->GetInput()->IsJump()) { return FALSE; }		//押されてるか
	
	return TRUE;
}
