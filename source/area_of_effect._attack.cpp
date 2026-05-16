#include<memory>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"attack_base.h"
#include"area_of_effect_attack.h"
#include"area_of_effect_attack_state.h"
#include"object_base.h"
#include"behavior_status.h"
#include"physics.h"
#include"physics_interface.h"
#include"vector_assistant.h"
#include"rigid_body.h"
#include"sphere.h"
#include"condition_timer.h"
#include"character_base.h"
#include"effect_manager.h"
#include"effect_end_state.h"
#include"animator_base.h"


AreaOfEffectAttack::AreaOfEffectAttack(std::weak_ptr<ObjectBase> owner, 
	std::string charge_anim,float min_coll_ratio, 
	float max_coll_ratio,VECTOR effect_scale, 
	float hit_radius, int effect_id,float activate_time)
	: AttackBase(owner,min_coll_ratio,max_coll_ratio)
	, activate_timer_(std::make_shared<ConditionTimer>(activate_time))
	, charge_anim_(charge_anim)
	, state_(AreaOfEffectAttackState::kCharge)
	, effect_pos_(VectorAssistant::VGetZero())
	, effect_rot_(VectorAssistant::VGetZero())
	, effect_scale_(effect_scale)
	, effect_id_(effect_id)
{
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Sphere>(hit_radius, VectorAssistant::VGetZero()),
		&effect_pos_, FALSE, TRUE, 0.f, 0.f);
}

AreaOfEffectAttack::~AreaOfEffectAttack()
{

}

void AreaOfEffectAttack::Init()
{
	// rigid_bodyの登録
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
	rigid_body_->NotActive();
	state_ = AreaOfEffectAttackState::kCharge();
}

void AreaOfEffectAttack::Entry()
{
	rigid_body_->NotActive();
	// このタイミングでターゲットの場所へeffectを配置(後々AOEのUI)
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	effect_pos_ = owner->GetAttackTargetPos();
	
	// アニメーションの再生
	owner->GetAnimator()->PlayRequest(charge_anim_);

	EffectManager::GetInstance().SetPos(effect_id_, effect_pos_);
	EffectManager::GetInstance().SetScale(effect_id_, effect_scale_);
	// タイマーの起動
	activate_timer_->Start();
	state_ = AreaOfEffectAttackState::kCharge();
}

BehaviorStatus AreaOfEffectAttack::Update()
{

	switch (state_)
	{
	case AreaOfEffectAttackState::kCharge:
		return UpdateCharge();
		break;

	case AreaOfEffectAttackState::kPlay:
		return UpdatePlay();
		break;

	}

	
	return BehaviorStatus::kRunning;
}

void AreaOfEffectAttack::Exit()
{
	rigid_body_->NotActive();
}

void AreaOfEffectAttack::Debug()
{

}

void AreaOfEffectAttack::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

BehaviorStatus AreaOfEffectAttack::UpdateCharge()
{
	// タイマーの更新
	activate_timer_->Update();

	if (activate_timer_->GetIsEnd())
	{
		// 当たり判定をactive
		rigid_body_->Active();
		// エフェクトの再生
		EffectManager::GetInstance().Play(effect_id_);
		// 次のステートへ
		state_ = AreaOfEffectAttackState::kPlay;
	}
	return BehaviorStatus::kRunning;
}

BehaviorStatus AreaOfEffectAttack::UpdatePlay()
{
	// エフェクトの割合がこえたら当たり判定をなくし、effectを終了させる
	if (EffectManager::GetInstance().GetRatio(effect_id_) > max_coll_ratio_)
	{
		rigid_body_->NotActive();
		EffectManager::GetInstance().End(effect_id_, EffectEndState::kTotal);
	}
	auto chara = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	//アニメーション終了時,completeを返す
	if(chara->GetAnimator()->GetNowAnimName() != charge_anim_){ return BehaviorStatus::kComplete; }
	return BehaviorStatus::kRunning;
}