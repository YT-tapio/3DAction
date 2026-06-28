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
#include"animator_base.h"
#include"vector_assistant.h"
#include"FPS.h"
#include"time.h"

ChasePlayer::ChasePlayer(std::weak_ptr<ObjectBase> owner,
	std::string my_anim_name, VECTOR* target_player_pos, float chase_speed)
	: BehaviorBase(owner)
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

}

BehaviorStatus ChasePlayer::Update()
{
	auto owner = owner_.lock();
	auto owner_physics = std::dynamic_pointer_cast<IPhysicsEventReceiver>(owner);
	// 変換できないものは失敗
	if (owner_physics == nullptr) { return BehaviorStatus::kFailure; }
	
	// プレイヤーとオーナーの距離を計算
	VECTOR dist = VSub(*target_player_pos_, owner->GetPosition());
	dist = VectorAssistant::VGetFlat(dist);
	VECTOR velocity = dist;
	if (VSize(velocity) > chase_speed_)
	{
		// スピードの調整
		velocity = VScale(VNorm(velocity), chase_speed_ * owner->GetTime()->GetFPSRate());
	}
	auto owner_rigid_body = owner_physics->GetRigidBody();
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
