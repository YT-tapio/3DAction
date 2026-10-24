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

TitlePlayerController::TitlePlayerController()
	: pos_(VGet(0.f, -8.5f, 0.f))
	, scale_(VectorAssistant::VGetSame(0.05f))
	, rotation_(VGet(0.f, RadianAssistant::TheNumRadian(90), 0.f))
{
	model_handle_ = ModelRepository::GetInstance().GetHandle("player_attacker");

	animator_ = std::make_shared<AnimatorBase>("title/player", model_handle_);
	time_ = std::make_shared<Time>();
	Setting();
}

TitlePlayerController::~TitlePlayerController()
{
	MV1DeleteModel(model_handle_);
}

void TitlePlayerController::Init()
{
	animator_->Init();
	time_->Init();
	Setting();

	animator_->PlayRequest("walking");
}

void TitlePlayerController::Update()
{
	time_->Update();
	Move();
	Setting();
	animator_->Update(time_);
}

void TitlePlayerController::Draw()
{
	MV1DrawModel(model_handle_);
}

void TitlePlayerController::Debug()
{
	// “ª•”‚ÌÀ•W‚ð•\Ž¦
	DrawSphere3D(head_pos_, 1.f, 20.f, Color::kWhite, Color::kWhite, TRUE);
}

const VECTOR TitlePlayerController::GetPos() const
{
	return pos_;
}

const VECTOR TitlePlayerController::GetHeadPos() const
{
	return head_pos_;
}

void TitlePlayerController::Move()
{
	VECTOR dir = VGet(-1.f, 0.f, 0.f);
	float speed = kWalkSpeed * time_->GetFPSRate();
	pos_ = VAdd(pos_, VScale(dir, speed));
}

void TitlePlayerController::Setting()
{
	head_pos_ = VAdd(pos_, VGet(0.f, kHeadVertical, 0.f));
	MV1SetScale(model_handle_, scale_);
	MV1SetPosition(model_handle_, pos_);
	MV1SetRotationXYZ(model_handle_, rotation_);
}

