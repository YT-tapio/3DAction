#include<memory>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"attack_base.h"
#include"jumping_attack_state.h"
#include"jumping_attack.h"
#include"behavior_status.h"
#include"physics_interface.h"
#include"condition_timer.h"
#include"character_base.h"
#include"animator_base.h"
#include"rigid_body.h"

JumpingAttack::JumpingAttack(std::weak_ptr<ObjectBase> owner, float min_coll_ratio, float max_coll_ratio,
	std::string my_anim_name)
	: AttackBase(owner,min_coll_ratio,max_coll_ratio)
	, jumping_timing_(0.f)
	, my_anim_name_(my_anim_name)
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

	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	if (owner == nullptr) { return BehaviorStatus::kFailure; }
	switch (jumping_state_)
	{
		// ジャンプの予備動作
		case JumpingAttackState::kStandby:
			return StandbyUpdate(owner);
			break;
		// 上昇中
		case JumpingAttackState::kJumping:
			return JumpingUpdate(owner);
			break;
		// 空中での待機
		case JumpingAttackState::kAirStandby:
			return AirStandbyUpdate(owner);
			break;
		// 落下中
		case JumpingAttackState::kFalling:
			return FallingUpdate(owner);
			break;
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


BehaviorStatus JumpingAttack::StandbyUpdate(std::shared_ptr<CharacterBase> owner)
{
	// ジャンプのタイミング：アニメーション基準
	if (owner->GetAnimator()->GetRatio(my_anim_name_) > jumping_timing_)
	{
		// オーナーをジャンプさせる
		// 初速を与えてステートを切り替え
		// owner->Jumping(5.f);
		jumping_state_ = JumpingAttackState::kJumping;
	}

	return BehaviorStatus::kRunning;
}

BehaviorStatus JumpingAttack::JumpingUpdate(std::shared_ptr<CharacterBase> owner)
{
	auto animator = owner->GetAnimator();
	// タイミングでanimationをstopさせる
	if (animator->GetRatio(my_anim_name_) > jumping_anim_stop_timing_) { animator->Stop(); }

	jumping_state_ = JumpingAttackState::kAirStandby;

	// このスタンバイ時にあいての上に、いとかなくちゃいけないのか
	// 攻撃対象の上にいるようにしておきますか

	return BehaviorStatus::kRunning;
}

BehaviorStatus JumpingAttack::AirStandbyUpdate(std::shared_ptr<CharacterBase> owner)
{
	// タイマー更新
	condition_timer_->Update();

	// 空中滞在時間を満たしたら
	if(condition_timer_->GetIsEnd())
	{
		// アニメーションの再生
		// 自分の位置をターゲットした的の位置の真上に設定
		owner->GetAnimator()->Start();
		
		// ターゲットの真上
		VECTOR attack_target_pos = VGet(0, 0, 0);// owner->GetAttackTargetPos();
		// ターゲットの上空のpos
		VECTOR attack_target_above_pos = VAdd(attack_target_pos, VGet(0.f, 5.f, 0.f));	// 単純な高さでいいな	
		owner->Teleport(attack_target_above_pos);	// 上空の位置へテレポート
		jumping_state_ = JumpingAttackState::kFalling;
	}

	return BehaviorStatus::kRunning;
}

BehaviorStatus JumpingAttack::FallingUpdate(std::shared_ptr<CharacterBase> owner)
{
	// 当たり判定のオン,オフをする 
	if (CheckActiveColl(owner))
	{
		// オン
		rigid_body_->Active();
	}
	else
	{
		// オフ
		rigid_body_->NotActive();
	}

	// オーナーが着地をしたらサクセスを返すように：owner->GetIsGround();
	if (FALSE) { return BehaviorStatus::kSuccess; }

	return BehaviorStatus::kRunning;
}

const bool JumpingAttack::CheckActiveColl(std::shared_ptr<CharacterBase> owner) const
{
	float anim_ratio = owner->GetAnimator()->GetRatio(my_anim_name_);

	if (anim_ratio < min_coll_ratio_) { return FALSE; }
	if (anim_ratio > max_coll_ratio_) { return FALSE; }

	return TRUE;
}