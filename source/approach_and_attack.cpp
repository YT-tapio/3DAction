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
#include"status_holder_interface.h"
#include"status.h"
#include"status_container.h"
#include"takable_damage_enemy_interface.h"
#include"takable_damage_player_interface.h"
#include"attack_type.h"
#include"sound_manager.h"

ApproachAndAttack::ApproachAndAttack(std::weak_ptr<ObjectBase> owner, const float& min_coll_ratio, const float& max_coll_ratio, const float& damage_rate, 
	const std::string& my_anim_name, const float approach_timing, const float approach_speed,const std::string& collider_tag)
	: AttackBase(owner,min_coll_ratio,max_coll_ratio,damage_rate)
	, pos_(VectorAssistant::VGetZero())
	, my_anim_name_(my_anim_name)
	, approach_timing_(approach_timing)
	, approach_speed_(approach_speed)
	, is_approached_(FALSE)
	, collider_tag_(collider_tag)
{
	// rigid_bodyを生成する
	auto collider = std::make_shared<Capsule>(10.f,1.f,VectorAssistant::VGetZero());
	rigid_body_ = std::make_shared<RigidBody>(collider, &pos_, FALSE, TRUE, 1.f, 1.f);
	
}

ApproachAndAttack::~ApproachAndAttack()
{

}

void ApproachAndAttack::Init()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag(collider_tag_);
	Physics::GetInstance().AddBody(rigid_body_);
}

void ApproachAndAttack::Entry()
{
	//printfDx("コンボ\n");
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
	//printfDx("%.2f\n", anim_ratio);
	// アプローチをまだしていない
	if (!is_approached_)
	{
		// アニメーションで判断 
		if (anim_ratio > approach_timing_)
		{
			// アプローチ
			Approach(owner);
			is_approached_ = TRUE;
			SoundManager::GetInstance().Play3DSound("double_punch");
		}
	}
	
	// アニメーションのタイミングで当たり判定のオン,オフ
	if (anim_ratio >= min_coll_ratio_ && anim_ratio <= max_coll_ratio_)
	{
		// 当たり判定の場所を更新
		UpdateCollisionPos(owner);
		rigid_body_->Active();
	}
	else
	{
		rigid_body_->NotActive();
	}

	// アニメーションが終了したらおわり
	if (owner->GetAnimator()->GetIsEnd(my_anim_name_)) 
	{ 
		return BehaviorStatus::kComplete;
	}

	return BehaviorStatus::kRunning;
}

void ApproachAndAttack::Exit()
{
	rigid_body_->NotActive();
}

void ApproachAndAttack::Debug()
{
	rigid_body_->Debug();
}

void ApproachAndAttack::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	//ダメージを与える
	auto owner = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner_.lock());
	if (owner == nullptr) { return; }
	auto owner_tag = owner->GetRigidBody()->GetTag();
	auto object_tag = object->GetRigidBody()->GetTag();

	// 対象にdamageを与える

	// ownerのtagが一緒の時はreturn
	if (owner_tag == object_tag) { return; }

	// ownerがplayer
	if (owner_tag == "player")
	{
		// objectがplayerからダメージを受ける対象なのか変換する
		if (auto takable_player = std::dynamic_pointer_cast<ITakableDamagePlayer>(object))
		{
			auto owner_status_container = std::dynamic_pointer_cast<IStatusHolder>(owner_.lock())->GetStatusContainer();
			takable_player->OnDamageFromPlayer(owner_status_container->GetPhysicalATK() * damage_rate_, AttackType::kPhysical);
		}
		return;
	}

	// ownerが敵なら
	if (owner_tag == "enemy")
	{
		//objectがenemyからダメージを受ける対象なのか変換する
		if (auto takable_enemy = std::dynamic_pointer_cast<ITakableDamageEnemy>(object))
		{
			auto owner_status_container = std::dynamic_pointer_cast<IStatusHolder>(owner_.lock())->GetStatusContainer();
			takable_enemy->OnDamageFromEnemy(owner_status_container->GetPhysicalATK() * damage_rate_, AttackType::kPhysical);
		}
		return;
	}
}

void ApproachAndAttack::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void ApproachAndAttack::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void ApproachAndAttack::Approach(std::shared_ptr<EnemyBase> owner)
{
	// アプローチする
	auto owner_pos = owner->GetPosition();
	auto target_pos = owner->GetAttackTargetPos();

	// プレイヤーまでの向き
	auto owner_to_target_dir = VectorAssistant::VGetDir(owner_pos, target_pos);
	auto owner_rot = VGet(0.f, VectorAssistant::VGetTan(VectorAssistant::VGetReverce(owner_to_target_dir)), 0.f);
	auto approach_velocity = VScale(VectorAssistant::VGetFlat(owner_to_target_dir), approach_speed_);
	owner->SetRotation(owner_rot);
	owner->GetRigidBody()->SetTargetVelocity(approach_velocity);

}

void ApproachAndAttack::UpdateCollisionPos(std::shared_ptr<EnemyBase> owner)
{
	// 当たり判定の位置更新
	// enemyの正面に当たり判定を出す
	VECTOR front_dir = owner->GetFrontDir();
	pos_ = VAdd(VScale(front_dir, 5.f), owner->GetPosition());
}