#include<fstream>
#include<sstream>
#include<unordered_map>
#include<memory>
#include<string>
#include"DxLib.h"
#include"attack_base.h"
#include"double_punch.h"
#include"behavior_status.h"
#include"rigid_body.h"
#include"capsule.h"
#include"vector_assistant.h"
#include"character_base.h"
#include"animator_base.h"
#include"physics.h"
#include"physics_interface.h"
#include"takable_damage_player_interface.h"
#include"takable_damage_enemy_interface.h"
#include"attack_type.h"
#include"status_holder_interface.h"
#include"status.h"
#include"status_container.h"
#include"sound_manager.h"

DoublePunch::DoublePunch(std::weak_ptr<ObjectBase> owner, std::string my_anim_name,
	float min_coll_ratio, float max_coll_ratio,VECTOR* pos,float vertical,float radius,float damage_rate)
	: AttackBase(owner,min_coll_ratio,max_coll_ratio,damage_rate)
	, my_anim_name_(my_anim_name)
	,pos_(VectorAssistant::VGetZero())
	, played_(FALSE)
{
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(radius,vertical,VectorAssistant::VGetZero()),
		&pos_, FALSE, TRUE, 1.f, 0.2f);
}

DoublePunch::~DoublePunch()
{
	
}

void DoublePunch::Init()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("double_punch");
	rigid_body_->NotActive();

	Physics::GetInstance().AddBody(rigid_body_);

}

void DoublePunch::Entry()
{
	VECTOR owner_pos = VectorAssistant::VGetZero();
	VECTOR front_dir = VectorAssistant::VGetZero();
	// アニメーションの再生
	if (auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		character->GetAnimator()->PlayRequest(my_anim_name_);

		// オーナーの位置を取得
		owner_pos = character->GetPosition();

		auto target_pos = character->GetAttackTargetPos();
		// プレイヤーの方向に向ける
		auto rot = VectorAssistant::VGetDir(target_pos, owner_pos);
		rot.y = VectorAssistant::VGetTan(rot);
		rot.x = 0.f;
		rot.z = 0.f;
		character->SetRotation(rot);
		// 正面方向を取得
		front_dir = character->GetFrontDir();
	}
	rigid_body_->NotActive();
	played_ = FALSE;

	// オーナーの正面方向に当たり判定を生成
	pos_ = VAdd(owner_pos, VScale(front_dir, 5.f));

	//printfDx("double_punch_entry\n");
}

BehaviorStatus DoublePunch::Update()
{
	if (CheckCollActive())
	{
		if (!played_)
		{
			rigid_body_->Active();
			played_ = TRUE;
			// 音の再生
			SoundManager::GetInstance().SetPos("double_punch", pos_);
			SoundManager::GetInstance().Play3DSound("double_punch");
		}
	}
	else
	{
		rigid_body_->NotActive();
	}
	//printfDx("double_punch\n");
	if (SuccessCondition()) { return BehaviorStatus::kComplete; }

	return BehaviorStatus::kRunning;
}

void DoublePunch::Exit()
{
	rigid_body_->NotActive();
	played_ = FALSE;
}

void DoublePunch::Draw()
{

}

void DoublePunch::Debug()
{
	rigid_body_->Debug();
}

void DoublePunch::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
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

void DoublePunch::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{
	
}

void DoublePunch::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	
}

const bool DoublePunch::CheckCollActive() const
{
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	auto anim_play_ratio = owner->GetAnimator()->GetRatio(my_anim_name_);
	if (coll_timing_min_ > anim_play_ratio) { return FALSE; }
	if (coll_timing_max_ < anim_play_ratio) { return FALSE; }
	return TRUE;
}

const bool DoublePunch::SuccessCondition() const
{
	if (!played_) { return FALSE; }
	auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	if (character->GetAnimator()->GetNowAnimName() == my_anim_name_) { return FALSE; }
	return TRUE;
}