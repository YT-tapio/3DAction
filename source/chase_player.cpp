#include<memory>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"behavior_base.h"
#include"chase_player.h"
#include"object_base.h"
#include"behavior_status.h"
#include"physics_interface.h"
#include"rigid_body.h"
#include"character_base.h"
#include"enemy_base.h"
#include"animator_base.h"
#include"vector_assistant.h"
#include"FPS.h"
#include"time.h"
#include"enemy_movement_supporter.h"

ChasePlayer::ChasePlayer(std::weak_ptr<ObjectBase> owner,std::weak_ptr<EnemyMovementSupporter> enemy_movement_supporter,
	std::string my_anim_name, VECTOR* target_player_pos, float chase_speed)
	: BehaviorBase(owner)
	, enemy_movement_supporter_(enemy_movement_supporter)
	, my_anim_name_(my_anim_name)
	, target_player_pos_(target_player_pos)
	, chase_speed_(chase_speed)
{

}

ChasePlayer::~ChasePlayer()
{

}

void ChasePlayer::Init()
{

}

void ChasePlayer::Entry()
{
	//printfDx("チェイス\n");
}

BehaviorStatus ChasePlayer::Update()
{
	auto owner = owner_.lock();
	auto enemy = std::dynamic_pointer_cast<EnemyBase>(owner);
	auto enemy_movement_supporter = enemy_movement_supporter_.lock();
	// 変換できないものは失敗
	if (enemy == nullptr) { return BehaviorStatus::kFailure; }
	if (enemy_movement_supporter == nullptr) { return BehaviorStatus::kFailure; }
	// プレイヤーとオーナーの距離を計算
	auto dist = VSub(*target_player_pos_, owner->GetPosition());
	dist = VectorAssistant::VGetFlat(dist);
	auto dir = enemy_movement_supporter->SupportMovement(enemy.get(), *target_player_pos_,VNorm(dist));
	dist = VScale(dir, VSize(dist));
	VECTOR velocity = dist;
	if (VSize(velocity) > chase_speed_)
	{
		// スピードの調整
		velocity = VScale(VNorm(velocity), chase_speed_ * owner->GetTime()->GetFPSRate());
	}
	auto owner_rigid_body = enemy->GetRigidBody();
	owner_rigid_body->SetTargetVelocity(velocity);

	if (auto character = std::dynamic_pointer_cast<CharacterBase>(owner))
	{
		// アニメーションの再生をリクエスト
		character->GetAnimator()->PlayRequest(my_anim_name_);
		character->SetRotation(VGet(0.f,VectorAssistant::VGetTan(VectorAssistant::VGetReverce(VNorm(dist))), 0.f));	// ターゲットに向けたい
	}

	if (VSize(dist) <= 10.f) { return BehaviorStatus::kComplete; }


	// 必ず成功を返す
	return BehaviorStatus::kRunning;
}

void ChasePlayer::Exit()
{

}

void ChasePlayer::Debug()
{

}
