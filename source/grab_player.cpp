#include<memory>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"grab_player.h"
#include"animator_base.h"
#include"rigid_body.h"
#include"vector_assistant.h"
#include"FPS.h"
#include"condition_timer.h"
#include"physics.h"

GrabPlayer::GrabPlayer(std::weak_ptr<AnimatorBase> owner_animator, std::weak_ptr<RigidBody> owner_rigid_body, VECTOR* owner_pos,VECTOR* target_pos, const float& time, const float& speed)
	: IBehavior()
	, owner_animator_(owner_animator)
	, owner_rigid_body_(owner_rigid_body)
	, timer_(std::make_unique<ConditionTimer>(time))
	, owner_pos_(owner_pos)
	, target_pos_(target_pos)
	, dir_(VectorAssistant::VGetZero())
	, vel_(VectorAssistant::VGetZero())
	, speed_(speed)
	, is_end_(FALSE)
{

}

GrabPlayer::~GrabPlayer()
{

}

void GrabPlayer::Init()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("grab");
	Physics::GetInstance().AddBody(rigid_body_);
	timer_->Init();
	is_end_ = FALSE;
}

void GrabPlayer::Entry()
{
	// アニメーションの再生を依頼
	auto animator = owner_animator_.lock();
	if (animator == nullptr) { return; }
	auto rigid_body = owner_rigid_body_.lock();
	if (rigid_body == nullptr) { return; }

	animator->PlayRequest("grab");

	vel_ = VectorAssistant::VGetZero();
	
	// ターゲットの場所に走る
	auto owner_pos = *owner_pos_;
	auto target_pos = *target_pos_;
	dir_ = VectorAssistant::VGetDir(owner_pos, target_pos);
	timer_->ReStart();

	is_end_ = FALSE;
}

BehaviorStatus GrabPlayer::Update()
{
	auto animator = owner_animator_.lock();
	if (animator == nullptr) { return BehaviorStatus::kFailure; }
	auto rigid_body = owner_rigid_body_.lock();
	if (rigid_body == nullptr) { return BehaviorStatus::kFailure; }
	timer_->Update();
	const float speed = speed_ * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS();
	vel_ = VScale(dir_, speed);
	// 速度を与える
	rigid_body->SetTargetVelocity(vel_);

	if (timer_->GetIsEnd()) { is_end_ = TRUE; }

	// 終了条件複数のためこの形
	if (is_end_)
	{
		return BehaviorStatus::kComplete;
	}

	return BehaviorStatus::kRunning;
}

void GrabPlayer::Exit()
{
	timer_->Stop();
	vel_ = VectorAssistant::VGetZero();
}

void GrabPlayer::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	if (object->GetRigidBody() == nullptr) { return; }
	auto other_tag = object->GetRigidBody()->GetTag();
	// 相手がplayerのときのみ
	if (other_tag == "player")
	{
		is_end_ = TRUE;
	}
}

std::shared_ptr<RigidBody> GrabPlayer::GetRigidBody()
{
	return rigid_body_;
}

