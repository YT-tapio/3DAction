#include<string>
#include<memory>
#include"DxLib.h"
#include"punch.h"
#include"vector_assistant.h"
#include"object_base.h"
#include"physics.h"
#include"rigid_body.h"
#include"capsule.h"
#include"debug.h"
#include"enemy_base.h"
#include"player.h"
#include"animator_base.h"
#include"behavior_status.h"
#include"takable_damage_player_interface.h"
#include"status.h"
#include"status_container.h"
#include"status_holder_interface.h"
#include"attack_type.h"
#include"time.h"
#include"effect_id.h"
#include"effect_manager.h"

Punch::Punch(std::weak_ptr<ObjectBase> owner, VECTOR* pos,
	std::string my_anim_name, float min_coll_ratio, float max_coll_ratio, std::shared_ptr<RigidBody> body)
	: AttackBase(owner, min_coll_ratio, max_coll_ratio)
	, my_anim_name_(my_anim_name)
{
	pos_ = pos;
	rigid_body_ = body;
	frame_ = 0;
}

Punch::~Punch()
{

}

void Punch::Init()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("punch");
	Physics::GetInstance().AddBody(rigid_body_);
	rigid_body_->NotActive();
}

BehaviorStatus Punch::Update()
{
	frame_++;
	// どうしよう
	// 正直今この中ではただ手に当たり判定を持たせているだけなんだよな
	// ownerにpunchを発生させたいよな
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	
	if (owner == nullptr) { return BehaviorStatus::kFailure; }
	auto owner_animator = owner->GetAnimator();
	if (owner_animator == nullptr) { return BehaviorStatus::kFailure; }

	//TODO：おわりのタイミングになったらsuccessするように

	float punch_play_time = owner_animator->GetRatio(my_anim_name_);
	// 当たり判定をのactiveをします
	if (punch_play_time > coll_timing_min_ && punch_play_time < coll_timing_max_) 
	{ 
		rigid_body_->Active();
	}
	else
	{
		rigid_body_->NotActive();
	}

	return BehaviorStatus::kRunning;
}

void Punch::Exit()
{
	rigid_body_->NotActive();
}

void Punch::Debug()
{
	rigid_body_->Debug();
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----AttackCollider----", GetColor(255, 255, 255));
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(*pos_);
}

void Punch::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto owner = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner_.lock());
	if (owner == nullptr) { return; }
	auto owner_tag = owner->GetRigidBody()->GetTag();
	auto object_tag = object->GetRigidBody()->GetTag();
	// タグが同じだと早期リターン
	if (owner_tag == object_tag) { return; }
	
	// タグが違う場合は相手にダメージを加える
	// ownerがpalyerだったら
	if (owner_tag == "player")
	{
		// objectがプレイヤーからダメージを受けるインターフェースを継承しているかをチェック
		if (auto takable_player = std::dynamic_pointer_cast<ITakableDamagePlayer>(object))
		{
			auto owner_status_container = std::dynamic_pointer_cast<IStatusHolder>(owner_.lock())->GetStatusContainer();
			takable_player->OnDamageFromPlayer(owner_status_container->GetPhysicalATK(), AttackType::kPhysical);
			// ヒットストップ
			owner_.lock()->GetTime()->SetTimeScale(0.f, 0.2f, TimeTransitionMethod::kMoment);
			// エフェクトの描画
			EffectManager::GetInstance().Play(EffectID::kPunchHit);
			EffectManager::GetInstance().SetPos(EffectID::kPunchHit, *pos_);
			//printfDx("damage:%.2f\n",)
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
			takable_enemy->OnDamageFromEnemy(owner_status_container->GetPhysicalATK(), AttackType::kPhysical);
		}
		return;
	}
}

void Punch::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{
	
}

void Punch::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}
