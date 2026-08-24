#include<string>
#include<unordered_map>
#include<memory>
#include<utility>
#include"DxLib.h"
#include"attack_base.h"
#include"stamp.h"
#include"object_base.h"
#include"behavior_status.h"
#include"capsule.h"
#include"sphere.h"
#include"physics.h"
#include"rigid_body.h"
#include"character_base.h"
#include"animator_base.h"
#include"takable_damage_player_interface.h"
#include"takable_damage_enemy_interface.h"
#include"attack_type.h"
#include"effect_id.h"
#include"effect_end_state.h"
#include"effect_manager.h"
#include"status_holder_interface.h"
#include"status.h"
#include"status_container.h"
#include"sound_manager.h"
#include<functional>
#include"brain.h"

Stamp::Stamp(std::weak_ptr<ObjectBase> owner, VECTOR* pos, float radius,std::string my_anim_name, float damage_rate)
	: AttackBase(owner,0,0,damage_rate)
	, is_stamp_(FALSE)
	, my_anim_name_(my_anim_name)
{
	//rigid_bodyを生成
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Sphere>(radius, VGet(0, 0, 0)), pos, FALSE, TRUE, 1.f, 1.f);
}

Stamp::~Stamp()
{

}

void Stamp::Init()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("stamp");
	Physics::GetInstance().AddBody(rigid_body_);
	rigid_body_->NotActive();
}

void Stamp::Entry()
{
	rigid_body_->NotActive();
	is_stamp_ = FALSE;
	//printfDx("stamp_entry\n");
}

BehaviorStatus Stamp::Update()
{
	if (is_stamp_) 
	{ 
		rigid_body_->NotActive();
		//違うアニメーションになればサクセスを返す
		if (auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
		{
			if(character->GetAnimator()->GetNowAnimName() != my_anim_name_)
			{
				return BehaviorStatus::kComplete;
			}
		}
	}

	// オーナーが着地したら成功を返します。
	if (auto owner_physics = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner_.lock()))
	{
		auto owner_rigid_body = owner_physics->GetRigidBody();

		// 着地の瞬間
		if (owner_rigid_body->GetIsLanding()) 
		{
			// この瞬間に当たり判定を発生する
			rigid_body_->Active();
			is_stamp_ = TRUE;
			EffectManager::GetInstance().Play(EffectID::kStamp);
			const VECTOR owner_pos = owner_.lock()->GetPosition();
			EffectManager::GetInstance().SetPos(EffectID::kStamp,owner_pos);
			SoundManager::GetInstance().SetPos("stamp", owner_pos);
			SoundManager::GetInstance().Play3DSound("stamp");
			Brain::GetInstance().ShakeCamera(1.f, 0.3f);
		}
	}

	// printfDx("stamp\n");

	return BehaviorStatus::kRunning;
}

void Stamp::Exit()
{
	// 当たり判定を消す
	rigid_body_->NotActive();
	is_stamp_ = FALSE;
}

void Stamp::Debug()
{
	rigid_body_->Debug();
}

void Stamp::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	// タグをとる
	auto owner = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner_.lock());
	if (owner == nullptr) { return; }
	auto owner_tag = owner->GetRigidBody()->GetTag();
	auto object_tag = object->GetRigidBody()->GetTag();

	if (owner_tag == object_tag) { return; }

	// オーナーが何者かを判別
	if (owner_tag == "player")
	{
		// playerからダメージを受ける対象に変換
		if (auto takable_player = std::dynamic_pointer_cast<ITakableDamagePlayer>(object))
		{
			auto owner_status_container = std::dynamic_pointer_cast<IStatusHolder>(owner_.lock())->GetStatusContainer();
			takable_player->OnDamageFromPlayer(owner_status_container->GetPhysicalATK() * damage_rate_, AttackType::kPhysical);
		}
		return;
	}

	// オーナーが何者かを判別
	if (owner_tag == "enemy")
	{
		//playerからダメージを受ける対象に変換
		if (auto takable_enemy = std::dynamic_pointer_cast<ITakableDamageEnemy>(object))
		{
			auto owner_status_container = std::dynamic_pointer_cast<IStatusHolder>(owner_.lock())->GetStatusContainer();
			takable_enemy->OnDamageFromEnemy(owner_status_container->GetPhysicalATK() * damage_rate_, AttackType::kPhysical);
		}
		return;
	}

}

void Stamp::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{
	//printfDx("あたっている\n");
}

void Stamp::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	//printfDx("あたっている\n");
}


void Stamp::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	//printfDx("あたっている\n");
}
