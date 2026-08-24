#include<functional>
#include"DxLib.h"
#include"brain.h"
#include"vector_assistant.h"
#include"tracking_camera.h"
#include"player.h"
#include"sphere_camera.h"
#include"player_group.h"
#include"won_camera.h"
#include"lose_camera.h"
#include"enemy_lock_on_camera.h"
#include"shake.h"

void Brain::Init()
{
	current_camera_ = "nothing";
	before_camera_ = "nothing";
}

void Brain::CreatePlaySceneVirtualCamera(VECTOR* camera_pos, VECTOR* target_pos, std::function<VECTOR()> enemy_center_pos, std::function<VECTOR()> enemy_dir)
{
	auto player_head_pos = PlayerGroup::GetInstance().GetCurrentPlayerHeadPos();
	//virtual_cameras_[kTracking] = std::make_shared<TrackingCamera>(PlayerGroup::GetInstance().GetCurrentPlayerHeadPos(), camera_pos, target_pos);
	virtual_cameras_[kSphere] = std::make_shared<SphereCamera>(player_head_pos, camera_pos, target_pos);
	
	virtual_cameras_["won"] = std::make_shared<WonCamera>(camera_pos, target_pos,enemy_center_pos,enemy_dir);
	virtual_cameras_["lose"] = std::make_shared<LoseCamera>(camera_pos, target_pos);
	virtual_cameras_["lock_on_enemy"] = std::make_shared<EnemyLockOnCamera>(camera_pos,target_pos, player_head_pos,enemy_center_pos);
	//virtual_cameras_[kTracking]->Init();
	
	for (auto& virtual_camera : virtual_cameras_)
	{
		camera_names_.push_back(virtual_camera.first);
		virtual_camera.second->Awake();
	}

	current_camera_ = kSphere;
	before_camera_ = kSphere;
}

void Brain::Update()
{
	// カメラの切り返したとき
	if (current_camera_ != before_camera_)
	{
		//カメラの初期化
		virtual_cameras_[current_camera_]->Init();
	}
	else
	{
		// カメラのupdateと切り替え
		// 切り替え
		// 現在のシーンを見て切り替えのチェンジ
		// VirtualCameraのupdate
		virtual_cameras_[current_camera_]->Update();

		vel_ = virtual_cameras_[current_camera_]->GetVelocity();
		target_vel_ = virtual_cameras_[current_camera_]->GetTargetVelocity();
	}
	shake_->Update();
	before_camera_ = current_camera_;
}


void Brain::DeleteVirtualCamera()
{
	virtual_cameras_.clear();
	camera_names_.clear();
}

void Brain::ChangeCamera(const std::string& request_name)
{
	for (const auto camera_name : camera_names_)
	{
		if (camera_name == request_name)
		{
			current_camera_ = request_name;
		}
	}
}

void Brain::ShakeCamera(const float& power,const float& time)
{
	if (power == 0.f || time == 0.f) { return; }
	shake_->Active(power, time);
}

void Brain::CollisionNotActive()
{

}

void Brain::CollisionActive()
{

}

const std::string Brain::GetCurrentCameraName() const
{
	return current_camera_;
}

const VECTOR Brain::GetVelocity() const
{
	return VAdd(vel_,shake_->GetShakeVel());
}

const VECTOR Brain::GetTargetVelocity() const
{
	return VAdd(target_vel_, shake_->GetShakeVel());
}

Brain::Brain()
	: vel_(VectorAssistant::VGetZero())
	, target_vel_(VectorAssistant::VGetZero())
	, can_hit_(TRUE)
	, shake_(std::make_shared<Shake>())
{

}