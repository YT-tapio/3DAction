#include<memory>
#include"DxLib.h"
#include"title_player_controller.h"
#include<string>
#include<unordered_map>
#include"animator_base.h"
#include"model_repository.h"
#include"time.h"
#include"vector_assistant.h"
#include"color.h"

#include"physics.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"capsule.h"

#include"brain.h"

#include"condition_timer.h"
#include"variable_timer.h"

TitlePlayerController::TitlePlayerController()
	: pos_(VGet(0.f, -8.5f, 0.f))
	, scale_(VectorAssistant::VGetSame(0.05f))
	, rotation_(VGet(0.f, RadianAssistant::TheNumRadian(90), 0.f))
	, phase_(Phase::kFirst)
{
	model_handle_ = ModelRepository::GetInstance().GetHandle("player_attacker");
	auto collider = std::make_shared<Capsule>(3.f, 10.f, VGet(0.f, 0.f, 0.f));
	rigid_body_ = std::make_shared<RigidBody>(collider, &pos_, FALSE, TRUE, 0.f, 1.f);
	animator_ = std::make_shared<AnimatorBase>("title/player", model_handle_);
	time_ = std::make_shared<Time>();
	offset_timer_ = std::make_shared<VariableTimer>(0.3f);
	Setting();
}

TitlePlayerController::~TitlePlayerController()
{
	MV1DeleteModel(model_handle_);
}

void TitlePlayerController::Awake()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("player");
	Physics::GetInstance().AddBody(rigid_body_);
	time_->Init();
	offset_timer_->Init();
	Setting();
}

void TitlePlayerController::Init()
{
	pos_ = VGet(0.f, -8.5f, 0.f);
	rotation_.y = RadianAssistant::TheNumRadian(90);
	phase_ = Phase::kFirst;
	animator_->Init();
	Setting();
	animator_->PlayRequest("walking");
	offset_timer_->Init();
	offset_timer_->ChangeMaxTime(0.3f);
}

void TitlePlayerController::Update()
{
	time_->Update();

	switch (phase_)
	{
	case Phase::kFirst:
		FirstPhaseUpdate();
		break;

	case Phase::kSecond:
		SecondPhaseUpdate();
		break;

	case Phase::kThird:
		ThirdPhaseUpdate();
		break;

	case Phase::kFourth:
		FourthPhaseUpdate();
		break;

	case Phase::kFifth:
		FifthPhaseUpdate();
		break;

	case Phase::kSix:
		SixPhaseUpdate();
		break;

	}
	animator_->Update(time_);
}

void TitlePlayerController::LateUpdate()
{
	Setting();
}

void TitlePlayerController::Draw()
{
	MV1DrawModel(model_handle_);
}

void TitlePlayerController::Debug()
{
	// 頭部の座標を表示
	DrawSphere3D(head_pos_, 1.f, 20.f, Color::kWhite, Color::kWhite, TRUE);
	rigid_body_->Debug();
}

void TitlePlayerController::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto other_rigid_body = object->GetRigidBody();
	if (other_rigid_body == nullptr) { return; }
	if (other_rigid_body->GetTag() == "enemy")
	{
		time_->SetTimeScale(0.3f, 1.0f);
		offset_timer_->ReStart();
		phase_ = Phase::kSecond;
		//printfDx("enemyと接触\n");
		// カメラをシェイク
		Brain::GetInstance().ShakeCamera(1.f, 0.2f);
		Brain::GetInstance().ZoomCamera(63.f, 0.2f, 1.f);
		animator_->PlayRequest("take_tackle");
	}
}

const VECTOR TitlePlayerController::GetPos() const
{
	return pos_;
}

const VECTOR TitlePlayerController::GetHeadPos() const
{
	return head_pos_;
}

std::shared_ptr<RigidBody> TitlePlayerController::GetRigidBody()
{
	return rigid_body_;
}

const float TitlePlayerController::GetDeltaTime() const
{
	return time_->GetDeltaTime();
}

void TitlePlayerController::FirstPhaseUpdate()
{
	auto dir = VGet(-1.f, 0.f, 0.f);
	auto speed = kWalkSpeed * time_->GetFPSRate();
	auto vel = VScale(dir, speed);
	pos_ = VAdd(pos_, vel);
	rigid_body_->SetTargetVelocity(vel);
}

void TitlePlayerController::SecondPhaseUpdate()
{
	// 時間をおいてカメラを切り替える
	offset_timer_->Update();

	if (offset_timer_->GetIsEndCurrentFrame())
	{
		Brain::GetInstance().ChangeCamera("title_second_camera");
	}

	// タックル終了時
	if (animator_->GetIsEnd("take_tackle"))
	{
		rotation_.y = RadianAssistant::kOneRad * -90;
		phase_ = Phase::kThird;
		Brain::GetInstance().ChangeCamera("title_third_camera");
		animator_->PlayRequest("standing_up");
	}
}

void TitlePlayerController::ThirdPhaseUpdate()
{
	if (animator_->GetRatio("turn")  > 0.3f)
	{
		phase_ = Phase::kFourth;
		Brain::GetInstance().ChangeCamera("title_fourth_camera");
		
	}
}

void TitlePlayerController::FourthPhaseUpdate()
{
	if (animator_->GetIsEnd("turn"))
	{
		rotation_.y = 0.f;
		pos_.x = -27.f;
		phase_ = Phase::kFifth;
		offset_timer_->Stop();
		offset_timer_->ChangeMaxTime(6.2f);
		offset_timer_->ReStart();
	}

}

void TitlePlayerController::FifthPhaseUpdate()
{
	offset_timer_->Update();

	if (offset_timer_->GetIsEndCurrentFrame())
	{
		animator_->PlayRequest("angry");
	}

	if (animator_->GetIsEnd("angry"))
	{
		phase_ = Phase::kSix;
		offset_timer_->Stop();
		offset_timer_->ChangeMaxTime(0.3f);
		offset_timer_->ReStart();
	}
	
}

void TitlePlayerController::SixPhaseUpdate()
{
	offset_timer_->Update();
	if (offset_timer_->GetIsEndCurrentFrame())
	{
		animator_->PlayRequest("flying_punch");
		Brain::GetInstance().ChangeCamera("title_fourth_camera");
	}

	if (!offset_timer_->GetIsEnd())
	{
		auto dir = VGet(0.f, 0.f, -1.f);
		auto speed = kWalkSpeed * time_->GetFPSRate();
		auto vel = VScale(dir, speed);
		pos_ = VAdd(pos_, vel);
		rigid_body_->SetTargetVelocity(vel);
	}

	if (animator_->GetRatio("flying_punch") > 0.48f)
	{
		animator_->Stop();
	}
}

void TitlePlayerController::Setting()
{
	head_pos_ = VAdd(pos_, VGet(0.f, kHeadVertical, 0.f));
	MV1SetScale(model_handle_, scale_);
	MV1SetPosition(model_handle_, pos_);
	MV1SetRotationXYZ(model_handle_, rotation_);
}

