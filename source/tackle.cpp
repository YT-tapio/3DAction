#include<memory>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"attack_base.h"
#include"tackle.h"
#include"behavior_status.h"
#include"physics.h"
#include"rigid_body.h"
#include"condition_timer.h"
#include"character_base.h"
#include"animator_base.h"
#include"vector_assistant.h"
#include"takable_damage_player_interface.h"
#include"takable_damage_enemy_interface.h"
#include"attack_type.h"
#include"effect_manager.h"
#include"effect_id.h"
#include"effect_end_state.h"
#include"status_holder_interface.h"
#include"status.h"
#include"status_container.h"
#include"sound_manager.h"
Tackle::Tackle(std::weak_ptr<ObjectBase> owner, std::shared_ptr<RigidBody> rigid_body,
	std::string anim_name,const float time, const float speed, float damage_rate)
	: AttackBase(owner,0.f,0.f,damage_rate)
	, activate_timer_(std::make_shared<ConditionTimer>(time))
	, anim_name_(anim_name)
	, vel_(VectorAssistant::VGetZero())
	, offset_vel_(VectorAssistant::VGetZero())
	, speed_(speed)
{
	rigid_body_ = rigid_body;
}

Tackle::~Tackle()
{

}

void Tackle::Init()
{
	vel_ = VectorAssistant::VGetZero();
	// rigid_bodyの登録
	rigid_body_->NotActive();
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
	rigid_body_->SetTag("tackle");
	activate_timer_->Init();
}

void Tackle::Entry()
{
	VECTOR dir = VectorAssistant::VGetZero();
	// おーなーのアニメーションを流す
	if (auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		owner->GetAnimator()->PlayRequest(anim_name_);
		dir = VectorAssistant::VGetDir(owner->GetPosition(), owner->GetAttackTargetPos());
		owner->SetRotation(VGet(0.f, VectorAssistant::VGetTan(VectorAssistant::VGetReverce(dir)), 0.f));
		vel_ = VScale(dir, speed_);
		offset_vel_ = VScale(dir, 20.f);
		offset_vel_.y = 22.f;
	}
	
	// 当たり判定発生と発生時間のタイマーを開始
	rigid_body_->Active();
	activate_timer_->Init();
	activate_timer_->ReStart();

	// effectの発生
	EffectManager::GetInstance().Play(EffectID::kTackle);
	EffectManager::GetInstance().SetPos(EffectID::kTackle, VAdd(owner_.lock()->GetPosition(), offset_vel_));
	EffectManager::GetInstance().SetRot(EffectID::kTackle, VGet(0.f, VectorAssistant::VGetTan(VNorm(vel_)), 0.f));
	SoundManager::GetInstance().SetPos("tackle",owner_.lock()->GetPosition());
	SoundManager::GetInstance().Play3DSound("tackle");
}

BehaviorStatus Tackle::Update()
{
	// タイマーの更新
	activate_timer_->Update();
	EffectManager::GetInstance().SetPos(EffectID::kTackle, VAdd(owner_.lock()->GetPosition(), offset_vel_));
	// 移動量を設定
	if (activate_timer_->GetIsEnd())
	{
		// アニメーションのキャンセルを有効に
		if(auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
		{
			owner->GetAnimator()->Cancel();
		}
		// 当たり判定をなくす
		rigid_body_->NotActive();
		// effectを消す
		EffectManager::GetInstance().End(EffectID::kTackle,EffectEndState::kMoment);
		return BehaviorStatus::kComplete;	// 終了を返す
	}
	else
	{
		if (auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
		{
			owner->GetAnimator()->PlayRequest(anim_name_);
		}
		if (auto owner = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner_.lock()))
		{
			owner->GetRigidBody()->SetTargetVelocity(vel_);
		}
	}
	

	return BehaviorStatus::kRunning;
}

void Tackle::Exit()
{
	rigid_body_->NotActive();
}

void Tackle::Debug()
{
	rigid_body_->Debug();
}

void Tackle::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto owner = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner_.lock());
	if (owner == nullptr) { return; }
	auto owner_tag = owner->GetRigidBody()->GetTag();
	auto object_tag = object->GetRigidBody()->GetTag();

	if (owner_tag == object_tag) { return; }

	// タグが違う場合は相手にダメージを加える
	// ownerがpalyerだったら
	if (owner_tag == "player")
	{
		// objectがプレイヤーからダメージを受けるインターフェースを継承しているかをチェック
		if (auto takable_player = std::dynamic_pointer_cast<ITakableDamagePlayer>(object))
		{
			auto owner_status_container = std::dynamic_pointer_cast<IStatusHolder>(owner_.lock())->GetStatusContainer();
			takable_player->OnDamageFromPlayer(owner_status_container->GetPhysicalATK() * damage_rate_, AttackType::kPhysical);
		}
		return;
	}

	// ownerがenemyだったら
	if (owner_tag == "enemy")
	{
		// objectがプレイヤーからダメージを受けるインターフェースを継承しているかをチェック
		if (auto takable_enemy = std::dynamic_pointer_cast<ITakableDamageEnemy>(object))
		{
			auto owner_status_container = std::dynamic_pointer_cast<IStatusHolder>(owner_.lock())->GetStatusContainer();
			takable_enemy->OnDamageFromEnemy(owner_status_container->GetPhysicalATK() * damage_rate_, AttackType::kPhysical);
		}
		return;
	}

}

void Tackle::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void Tackle::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}
