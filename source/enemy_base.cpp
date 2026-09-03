#include<iostream>
#include<memory>
#include<string>
#include<functional>
#include<utility>
#include"DxLib.h"
#include"enemy_base.h"
#include"sphere.h"
#include"capsule.h"
#include"rigid_body.h"
#include"FPS.h"
#include"vector_assistant.h"
#include"debug.h"
#include"physics.h"
#include"object_setter.h"
#include"animator_base.h"
#include"animator_enemy.h"
#include"punch.h"
#include"check_my_area.h"
#include"behavior_tree.h"
#include"behavior_status.h"
#include"behavior_base.h"
#include"character_behavior.h"
#include"double_punch.h"
#include"jumping_attack.h"
#include"area_of_effect_attack.h"
#include"jump.h"
#include"stamp.h"
#include"tackle.h"
#include"animation_charge.h"
#include"chase_player.h"
#include"color.h"
#include"node_base.h"
#include"composite_node.h"
#include"selector_node.h"
#include"sequence_node.h"
#include"random_node.h"
#include"branch_node.h"
#include"action_node.h"
#include"player_group.h"
#include"effect_id.h"
#include"attack_type.h"
#include"status.h"
#include"status_container.h"
#include"disp_attack_range.h"
#include"enemy_ui_group.h"
#include"time.h"
#include"change_method.h"
#include"hit_red_body.h"
#include"damage_ui_group.h"
#include"play_sound.h"
#include"roar.h"
#include"just_one_node.h"
#include"brain.h"
#include"sound_manager.h"
#include"enemy_observer_interface.h"
#include"enemy_cool_time_controller.h"
#include"enemy_ui_group_interface.h"
#include"damage_ui_group_interface.h"

EnemyBase::EnemyBase(const VECTOR& pos,bool* game_start,std::shared_ptr<IEnemyUIGroup> enemy_ui_group,
	std::shared_ptr<IDamageUIGroup> damage_ui_group, std::shared_ptr<IPlayerGroup> player_group)
	: CharacterBase("enemy")
	, IPhysicsEventReceiver()
	, game_start_(game_start)
	, hips_pos_(VectorAssistant::VGetZero())
	, disp_attack_flat_pos_(VectorAssistant::VGetZero())
	, flat_hips_pos_(VectorAssistant::VGetZero())
	, phase_(Phase::first)
	, cool_time_(std::make_shared<EnemyCoolTimeController>())
	, enemy_ui_group_(enemy_ui_group)
	, damage_ui_group_(damage_ui_group)
	, player_group_(player_group)
{
	
}

EnemyBase::~EnemyBase()
{
	
}

void EnemyBase::AddObserver(IEnemyObserver* observer)
{
	observers_.push_back(observer);
}

void EnemyBase::Init()
{
	
}

void EnemyBase::Update()
{
	//printfDx("%.2f\n", rigid_body_->GetFallSpeed());
	
}

void EnemyBase::LateUpdate()
{

}

void EnemyBase::Draw()
{
	hit_red_body_->DoRedColor();
	
	MV1DrawModel(handle_);
}

void EnemyBase::Debug()
{
	if (FALSE) { return; }

	status_container_->Debug();

	behavior_tree_->Debug();
	rigid_body_->Debug();
	if (TRUE) { return; }
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "----------enemy-----------", Color::kWhite);
	Debug::GetInstance().Add();
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "pos", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(pos_);
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "target_player_pos", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(target_player_pos_);
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "%s", animator_->GetNowAnimName().c_str());
	Debug::GetInstance().Add();

	// test_behavior_->Debug();
}

void EnemyBase::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto target_tag = object->GetRigidBody()->GetTag();
	if (target_tag == "punch")
	{
		if (!object->GetRigidBody()->CheckSameOwner(shared_from_this()))
		{
			// animator_->PlayRequest("on_damage");
		}
	}
}

void EnemyBase::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void EnemyBase::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void EnemyBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto target_tag = object->GetRigidBody()->GetTag();
	if (target_tag == "punch")
	{
		if (!object->GetRigidBody()->CheckSameOwner(shared_from_this()))
		{
			// animator_->PlayRequest("on_damage");
		}
	}
}

void EnemyBase::OnGround(std::shared_ptr<IPhysicsEventReceiver> object)
{
	is_ground_ = TRUE;
	fall_speed_ = 0.f;
	vel_.y = 0.f;
}

void EnemyBase::UnGround()
{
	is_ground_ = FALSE;
}

void EnemyBase::OnDamageFromPlayer(float damage,AttackType type)
{
	auto final_damage = status_container_->TakeDamage(damage,type);
	Brain::GetInstance().ShakeCamera(0.3f, 0.2f);
	for (auto& observer : observers_)
	{
		observer->OnTakeDamage(final_damage);
	}
	damage_ui_group_->SpawnEnemyDamageUI(VAdd(pos_, VGet(0.f, 5.f, 0.f)), final_damage);
	// ‘Ì‚ðÔ‚­‚·‚é
	hit_red_body_->Request(ChangeMethod::kLerp, 0.2f);

	if (status_container_->GetCurrentStatus().hp <= 0)
	{
		Death();
	}

}

const bool EnemyBase::GetOnGround() const
{
	return rigid_body_->GetOnGround();
}

std::shared_ptr<StatusContainer> EnemyBase::GetStatusContainer()
{
	return status_container_;
}

std::shared_ptr<RigidBody> EnemyBase::GetRigidBody()
{
	return rigid_body_;
}

const float EnemyBase::GetDeltaTime() const
{
	return time_->GetFPSRate();
}

const VECTOR EnemyBase::GetAttackTargetPos() const
{
	return target_player_pos_;
}

const VECTOR EnemyBase::GetCenterPos() const
{
	VECTOR center_pos = VAdd(pos_, VGet(0.f, 6.f, 0.f));
	return center_pos;
}

void EnemyBase::LoadFile()
{

}

void EnemyBase::UpdateBone()
{
	int hand_bone_num = 0;
	int hips_num = 0;
	const TCHAR* hand_bone_path = "mixamorig:RightHand";
	const TCHAR* hips_path = "mixamorig:Hips";
	hips_num = MV1SearchFrame(handle_, hips_path);
	MATRIX hand_mat = MV1GetFrameLocalWorldMatrix(handle_, hand_bone_num);
	MATRIX hips_mat = MV1GetFrameLocalWorldMatrix(handle_, hand_bone_num);
	VECTOR right_hand_pos = VectorAssistant::VGetPositionFromMatrix(hand_mat);
	VECTOR hips_pos = VectorAssistant::VGetPositionFromMatrix(hips_mat);
	right_hand_pos_ = right_hand_pos;
	hips_pos_ = hips_pos;
	disp_attack_flat_pos_ = target_player_pos_;
	disp_attack_flat_pos_.y = -17.5f;
	flat_hips_pos_ = hips_pos_;
	flat_hips_pos_.y = pos_.y;
}

void EnemyBase::Death()
{
	Brain::GetInstance().ChangeCamera("won");
	rigid_body_->NotActive();
	animator_->PlayRequest("death");
	SoundManager::GetInstance().Stop("game_bgm");

	for (auto observer : observers_)
	{
		observer->OnEnemyDeath();
	}
}