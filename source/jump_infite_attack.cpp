#include<memory>
#include"DxLib.h"
#include"object_base.h"
#include"jump_infite_attack.h"
#include"behavior_status.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"capsule.h"
#include"vector_assistant.h"
#include<string>
#include<unordered_map>
#include"character_base.h"
#include"animator_base.h"
#include"physics.h"
#include"player.h"
#include"takable_damage_enemy_interface.h"
#include"takable_damage_player_interface.h"
#include"attack_type.h"
#include"status.h"
#include"status_container.h"


JumpInfiteAttack::JumpInfiteAttack(std::weak_ptr<ObjectBase> owner, float min_coll_ratio, float max_coll_ratio, float damage_rate)
	: AttackBase(owner,min_coll_ratio,max_coll_ratio,damage_rate)
{
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(3.f, 1.f, VectorAssistant::VGetZero()), &pos_, FALSE, TRUE, 1.f, 1.f);
}

JumpInfiteAttack::~JumpInfiteAttack()
{

}

void JumpInfiteAttack::Init()
{
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
	rigid_body_->NotActive();
}

void JumpInfiteAttack::Entry()
{
	// アニメーションの再生
	if (auto character = std::dynamic_pointer_cast<Player>(owner_.lock()))
	{
		character->GetAnimator()->PlayRequest("jump_infite_attack");
	}
}

BehaviorStatus JumpInfiteAttack::Update()
{
	// rigid_body_->Debug();
	// アニメーションの割合によってrigid_bodyのオン,オフ
	if (auto character = std::dynamic_pointer_cast<Player>(owner_.lock()))
	{
		if (character->GetAnimator()->GetNowAnimName() != "jump_infite_attack") { return BehaviorStatus::kComplete; }

		// rigid_bodyのオン、オフ
		auto anim_ratio = character->GetAnimator()->GetRatio("jump_infite_attack");

		// 当たり判定のポジション更新
		auto owner_pos = character->GetHipPos();
		auto owner_front_dir = character->GetFrontDir();

		pos_ = VAdd(owner_pos, VScale(owner_front_dir, 2.f));
		pos_.y -= 1.f;

		if (anim_ratio > coll_timing_min_ && anim_ratio < coll_timing_max_)
		{
			rigid_body_->Active();
		}
		else
		{
			rigid_body_->NotActive();
		}
	}
	else
	{
		return BehaviorStatus::kFailure;
	}

	return BehaviorStatus::kFailure;
}

void JumpInfiteAttack::Exit()
{
	rigid_body_->NotActive();
}

void JumpInfiteAttack::Debug()
{
	rigid_body_->Debug();
}

void JumpInfiteAttack::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	int i = 0;
	i++;
	//printfDx("何かと当たった\n");
	//printfDx("%d\n", i);

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

void JumpInfiteAttack::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void JumpInfiteAttack::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}