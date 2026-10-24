#include<memory>
#include"DxLib.h"
#include"title_enemy_controller.h"
#include"time.h"
#include<string>
#include<unordered_map>
#include"animator_base.h"
#include"vector_assistant.h"
#include"model_repository.h"

TitleEnemyController::TitleEnemyController()
	: pos_(VGet(-40.1f, -8.5f, 166.7f))
	, scale_(VectorAssistant::VGetSame(0.05f))
	, rotation_(VGet(0.f, RadianAssistant::TheNumRadian(0), 0.f))
{
	model_handle_ = ModelRepository::GetInstance().GetHandle("zako");

	animator_ = std::make_shared<AnimatorBase>("title/zako", model_handle_);
	time_ = std::make_shared<Time>();
}

TitleEnemyController::~TitleEnemyController()
{
	MV1DeleteModel(model_handle_);
}

void TitleEnemyController::Init()
{
	animator_->Init();
	time_->Init();
	animator_->PlayRequest("tackle");
	Setting();
}

void TitleEnemyController::Update()
{
	time_->Update();
	Move();
	Setting();
	animator_->Update(time_);
}

void TitleEnemyController::Draw()
{
	MV1DrawModel(model_handle_);
	
}

void TitleEnemyController::Debug()
{

}

void TitleEnemyController::Move()
{
	auto dir = VGet(0.f, 0.f, -1.f);
	auto vel = VScale(dir, kDashSpeed);
	pos_ = VAdd(pos_, vel);
}

void TitleEnemyController::Setting()
{
	MV1SetScale(model_handle_, scale_);
	MV1SetPosition(model_handle_, pos_);
	MV1SetRotationXYZ(model_handle_, rotation_);
}