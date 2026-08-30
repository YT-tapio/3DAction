#include<memory>
#include<string>
#include<vector>
#include"DxLib.h"
#include"approach_and_attack.h"
#include"behavior_status.h"
#include"character_base.h"
#include"enemy_base.h"
#include<unordered_map>
#include"animator_base.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"capsule.h"
#include"vector_assistant.h"
#include"physics.h"
#include"physics_interface.h"

ApproachAndAttack::ApproachAndAttack(std::weak_ptr<ObjectBase> owner, const float& min_coll_ratio, const float& max_coll_ratio, const float& damage_rate, 
	const std::string& my_anim_name, const float approach_timing, const float approach_speed)
	: AttackBase(owner,min_coll_ratio,max_coll_ratio,damage_rate)
	, pos_(VectorAssistant::VGetZero())
	, my_anim_name_(my_anim_name)
	, approach_timing_(approach_timing)
	, approach_speed_(approach_speed)
	, is_approached_(FALSE)
{
	// rigid_bodyを生成する
	auto collider = std::make_shared<Capsule>(3.f,1.f,VectorAssistant::VGetZero());
	rigid_body_ = std::make_shared<RigidBody>(collider, &pos_, FALSE, TRUE, 1.f, 1.f);

}

ApproachAndAttack::~ApproachAndAttack()
{

}

void ApproachAndAttack::Init()
{
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
}

void ApproachAndAttack::Entry()
{
	// アニメーションを再生する
	if (auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		owner->GetAnimator()->PlayRequest(my_anim_name_);
	}
	is_approached_ = FALSE;
}

BehaviorStatus ApproachAndAttack::Update()
{
	// 再生中のアニメーションのratioを受け取りそのratioに達したらちかづく
	auto owner = std::dynamic_pointer_cast<EnemyBase>(owner_.lock());
	if (owner == nullptr) { return BehaviorStatus::kFailure; }

	auto anim_ratio = owner->GetAnimator()->GetRatio(my_anim_name_);

	// 

	// アプローチをまだしていない
	if (!is_approached_)
	{
		// アニメーションで判断 
		if (anim_ratio > approach_timing_)
		{
			// アプローチ
			Approach(owner);
			is_approached_ = TRUE;
		}
	}
	
	// アニメーションのタイミングで当たり判定のオン,オフ
	if (anim_ratio >= min_coll_ratio_ && anim_ratio <= max_coll_ratio_)
	{
		// 当たり判定の場所を更新

		rigid_body_->Active();
	}
	else
	{
		rigid_body_->NotActive();
	}

	// アニメーションが終了したらおわり
	if (owner->GetAnimator()->GetIsEnd(my_anim_name_)) { return BehaviorStatus::kComplete; }

	return BehaviorStatus::kRunning;
}

void ApproachAndAttack::Exit()
{
	rigid_body_->NotActive();
}

void ApproachAndAttack::Approach(std::shared_ptr<EnemyBase> owner)
{
	// アプローチする
	auto owner_pos = owner->GetPosition();
	auto target_pos = owner->GetAttackTargetPos();

	// プレイヤーまでの向き
	auto owner_to_target_dir = VectorAssistant::VGetDir(owner_pos, target_pos);
	auto owner_rot = VGet(0.f, VectorAssistant::VGetTan(owner_to_target_dir), 0.f);
	auto approach_velocity = VScale(VectorAssistant::VGetFlat(owner_to_target_dir), approach_speed_);
	owner->SetRotation(owner_rot);
	owner->GetRigidBody()->SetTargetVelocity(approach_velocity);

}
