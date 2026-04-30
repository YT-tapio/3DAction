#include<memory>
#include"DxLib.h"
#include"attack_base.h"
#include"jumping_attack_state.h"
#include"jumping_attack.h"
#include"behavior_status.h"
#include"physics_interface.h"
#include"condition_timer.h"

JumpingAttack::JumpingAttack(std::weak_ptr<ObjectBase> owner, float min_coll_ratio, float max_coll_ratio)
	: AttackBase(owner,min_coll_ratio,max_coll_ratio)
{
	condition_timer_ = std::make_shared<ConditionTimer>(0.5f);
	jumping_state_ = JumpingAttackState::kStandby;
}

JumpingAttack::~JumpingAttack()
{

}

void JumpingAttack::Init()
{
	
}

BehaviorStatus JumpingAttack::Update()
{
	// スタンプのような攻撃
	switch (jumping_state_)
	{
		// ジャンプの予備動作
		case JumpingAttackState::kStandby:
		{

			break;
		}

		// 上昇中
		case JumpingAttackState::kJumping:
		{
			break;
		}

		// 空中での待機
		case JumpingAttackState::kAirStandby:
		{
			condition_timer_->Start();
			jumping_state_ = JumpingAttackState::kJumping;
			break;
		}

		// 落下中
		case JumpingAttackState::kFalling:
		{
			break;
		}

	}




	return BehaviorStatus::kFailure;
}

void JumpingAttack::Exit()
{

}

void JumpingAttack::Draw()
{

}

void JumpingAttack::Debug()
{

}

void JumpingAttack::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}


