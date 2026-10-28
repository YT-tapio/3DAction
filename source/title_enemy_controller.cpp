#include<memory>
#include"DxLib.h"
#include"title_enemy_controller.h"
#include"time.h"
#include<string>
#include<unordered_map>
#include"animator_base.h"
#include"vector_assistant.h"
#include"model_repository.h"

#include"physics.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"capsule.h"

#include"condition_timer.h"
#include"variable_timer.h"

#include"brain.h"

TitleEnemyController::TitleEnemyController()
	: pos_(VGet(-27.1f, -8.5f, 115.7f))
	, scale_(VectorAssistant::VGetSame(0.05f))
	, rotation_(VGet(0.f, RadianAssistant::TheNumRadian(0), 0.f))
	,phase_(Phase::kFirst)
{
	model_handle_ = ModelRepository::GetInstance().GetHandle("zako");
	auto collider = std::make_shared<Capsule>(3.f, 10.f, VGet(0.f, 0.f, 0.f));

	rigid_body_ = std::make_shared<RigidBody>(collider, &pos_, FALSE, FALSE, 0.f, 1.f);

	animator_ = std::make_shared<AnimatorBase>("title/zako", model_handle_);
	time_ = std::make_shared<Time>();
	timer_ = std::make_shared<VariableTimer>(6.f);
}

TitleEnemyController::~TitleEnemyController()
{
	MV1DeleteModel(model_handle_);
}

void TitleEnemyController::Awake()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("enemy");
	Physics::GetInstance().AddBody(rigid_body_);
	time_->Init();
}

void TitleEnemyController::Init()
{
	pos_ = VGet(-27.1f, -8.5f, 115.7f);
	animator_->Init();
	Setting();
	animator_->PlayRequest("tackle");
	timer_->Init();
	timer_->ChangeMaxTime(6.f);
	timer_->ReStart();
}

void TitleEnemyController::Update()
{
	time_->Update();
	timer_->Update();
	
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
	}

	animator_->Update(time_);
}

void TitleEnemyController::LateUpdate()
{
	Setting();
}

void TitleEnemyController::Draw()
{
	MV1DrawModel(model_handle_);
}

void TitleEnemyController::Debug()
{
	rigid_body_->Debug();
}

void TitleEnemyController::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto other_rigid_body = object->GetRigidBody();
	if (other_rigid_body == nullptr) { return; }
	if (other_rigid_body->GetTag() == "player")
	{
		//printfDx("player�ƐڐG\n");
		time_->SetTimeScale(0.2f, 1.0f);
	}

}



std::shared_ptr<RigidBody> TitleEnemyController::GetRigidBody()
{
	return rigid_body_;
}

void TitleEnemyController::Move()
{
	
}

void TitleEnemyController::Setting()
{
	MV1SetScale(model_handle_, scale_);
	MV1SetPosition(model_handle_, pos_);
	MV1SetRotationXYZ(model_handle_, rotation_);
}

void TitleEnemyController::FirstPhaseUpdate()
{
	if (timer_->GetIsEnd())
	{
		rigid_body_->ResetVelocity();
		phase_ = Phase::kSecond;
		animator_->PlayRequest("idle");

		timer_->Stop();
		timer_->ChangeMaxTime(7.1f);
		timer_->ReStart();

		return;
	}
	auto dir = VGet(0.f, 0.f, -1.f);
	auto speed = kDashSpeed * time_->GetFPSRate();
	auto vel = VScale(dir, speed);
	rigid_body_->SetTargetVelocity(vel);
}

void TitleEnemyController::SecondPhaseUpdate()
{
	if (timer_->GetIsEndCurrentFrame())
	{
		animator_->PlayRequest("turn");
	}
	
	if (animator_->GetIsEnd("turn"))
	{
		animator_->PlayRequest("taunt");
		rotation_.y = RadianAssistant::kOneRad * 180.f;
	}

	if (animator_->GetRatio("taunt") > 0.85f)
	{
		Brain::GetInstance().ChangeCamera("title_fifth_camera");
		animator_->PlayRequest("idle");
		timer_->Stop();
		timer_->ChangeMaxTime(3.2f);
		timer_->ReStart();
		phase_ = Phase::kThird;
	}

}

void TitleEnemyController::ThirdPhaseUpdate()
{
	if (timer_->GetIsEndCurrentFrame())
	{
		animator_->PlayRequest("tackle");
		timer_->Stop();
		timer_->ChangeMaxTime(0.3f);
		timer_->ReStart();
		phase_ = Phase::kFourth;
	}
}

void TitleEnemyController::FourthPhaseUpdate()
{
	if (timer_->GetIsEndCurrentFrame())
	{
		Brain::GetInstance().ChangeCamera("title_six_camera");
		phase_ = Phase::kFifth; 
		timer_->Stop();
		timer_->ChangeMaxTime(1.f);
		timer_->ReStart();
	}
	else
	{
		auto dir = VGet(0.f, 0.f, 1.f);
		auto speed = 0.1f * time_->GetFPSRate();
		auto vel = VScale(dir, speed);
		rigid_body_->SetTargetVelocity(vel);
	}
}

void TitleEnemyController::FifthPhaseUpdate()
{
	if (timer_->GetIsEnd())
	{
		rigid_body_->ResetVelocity();
		animator_->Stop();
	}
	else
	{
		auto dir = VGet(0.f, 0.f, 1.f);
		auto speed = 0.1f * time_->GetFPSRate();
		auto vel = VScale(dir, speed);
		rigid_body_->SetTargetVelocity(vel);
	}

}
