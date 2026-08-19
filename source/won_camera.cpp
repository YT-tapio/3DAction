#include<functional>
#include<memory>
#include"DxLib.h"
#include"won_camera.h"
#include"lerp.h"
#include"fps.h"
#include"condition_timer.h"
#include<unordered_map>
#include"brain.h"
#include"player_group.h"

WonCamera::WonCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos, std::function<VECTOR()> enemy_center_pos, 
	std::function<VECTOR()> enemy_dir)
	: VirtualCameraBase(main_camera_pos, main_camera_target_pos)
	, enemy_center_pos_(enemy_center_pos)
	, enemy_dir_(enemy_dir)
	, enemy_target_offset_(VGet(0.f, 10.f, 0.f))
	, player_target_offset_(VGet(0.f,-5.f,0.f))
	, future_pos_(VectorAssistant::VGetZero())
	, future_target_pos_(VectorAssistant::VGetZero())
{
	timer_ = std::make_shared<ConditionTimer>(3.f);

	player_cneter_pos_ = PlayerGroup::GetInstance().GetCurrentPlayerHeadPos();
	player_dir_ = PlayerGroup::GetInstance().GetCurrentPlayerFrontDir();
}

WonCamera::~WonCamera()
{

}

void WonCamera::Init()
{
	// 敵の正面へ移動
	//printfDx("x:%.2f,y:%.2f,z:%.2f\n", future_pos_.x, future_pos_.y, future_pos_.z);
	VECTOR enemy_dir = enemy_dir_();
	future_pos_ = VScale(enemy_dir, kCameraToEnemyDistSize);
	auto enemy_center_pos = enemy_center_pos_();
	future_pos_ = VAdd(future_pos_, enemy_center_pos);
	//printfDx("x:%.2f,y:%.2f,z:%.2f\n", future_pos_.x, future_pos_.y, future_pos_.z);
	future_pos_ = VAdd(future_pos_, enemy_target_offset_);
	// printfDx("x:%.2f,y:%.2f,z:%.2f\n", future_pos_.x, future_pos_.y, future_pos_.z);
	vel_ = VectorAssistant::VGetZero();
	timer_->ReStart();
	future_target_pos_ = enemy_center_pos;
}

void WonCamera::Update()
{
	timer_->Update();
	// 時間がたてばもともとのカメラに戻る
	if (timer_->GetIsEnd())
	{
		// Brain::GetInstance().ChangeCamera("Sphere");

		// プレイヤーの少し横に行くように調整する前に行く

		VECTOR offset_dir = VectorAssistant::VGetRotRadY(*player_dir_, -80.f);
		VECTOR offset_target_pos = VScale(VectorAssistant::VGetFlat(offset_dir), kOffsetDist);
		VECTOR offset_pos = VAdd(offset_target_pos, VScale(*player_dir_, kCameraToPlayerDistSize));
		//player_target
		future_pos_ = VAdd(*player_cneter_pos_, offset_pos);
		future_target_pos_ = VAdd(*player_cneter_pos_, offset_target_pos);
		future_pos_ = VAdd(future_pos_, player_target_offset_);
		future_target_pos_ = VAdd(future_target_pos_, player_target_offset_);
	}
	float camera_speed = 1.3f * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS();
	float camera_target_speed = 1.f * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS();
	VECTOR main_camera_pos = *main_camera_pos_;
	VECTOR enemy_center_pos = enemy_center_pos_();
	VECTOR main_camera_target_pos = *main_camera_target_pos_;
	vel_ = VSub(Lerp::LerpV(main_camera_pos , future_pos_, camera_speed), main_camera_pos);
	// 敵の中心点が真ん中
	target_vel_ = VSub(Lerp::LerpV(main_camera_target_pos, future_target_pos_, camera_target_speed),main_camera_target_pos);
	
}