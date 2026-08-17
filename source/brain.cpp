#include<functional>
#include"DxLib.h"
#include"brain.h"
#include"vector_assistant.h"
#include"tracking_camera.h"
#include"player.h"
#include"sphere_camera.h"
#include"player_group.h"
#include"won_camera.h"

void Brain::Init()
{
	now_camera_ = "nothing";
	before_camera_ = "nothing";
}

void Brain::CreatePlaySceneVirtualCamera(VECTOR* camera_pos, VECTOR* target_pos, std::function<VECTOR()> enemy_center_pos, std::function<VECTOR()> enemy_dir)
{
	//virtual_cameras_[kTracking] = std::make_shared<TrackingCamera>(PlayerGroup::GetInstance().GetCurrentPlayerHeadPos(), camera_pos, target_pos);
	virtual_cameras_[kSphere] = std::make_shared<SphereCamera>(PlayerGroup::GetInstance().GetCurrentPlayerHeadPos(), camera_pos, target_pos);
	virtual_cameras_["won"] = std::make_shared<WonCamera>(camera_pos, target_pos,enemy_center_pos,enemy_dir);
	//virtual_cameras_[kTracking]->Init();
	
	for (auto& virtual_camera : virtual_cameras_)
	{
		virtual_camera.second->Awake();
	}

	now_camera_ = kSphere;
	now_camera_ = kSphere;
}

void Brain::Update()
{
	// カメラの切り返したとき
	if (now_camera_ != before_camera_)
	{
		//カメラの初期化
		virtual_cameras_[now_camera_]->Init();
	}
	else
	{
		// カメラのupdateと切り替え
		// 切り替え
		// 現在のシーンを見て切り替えのチェンジ
		// VirtualCameraのupdate
		virtual_cameras_[now_camera_]->Update();

		vel_ = virtual_cameras_[now_camera_]->GetVelocity();
		target_vel_ = virtual_cameras_[now_camera_]->GetTargetVelocity();
	}
	
	before_camera_ = now_camera_;
}


void Brain::DeleteVirtualCamera()
{
	virtual_cameras_.clear();
}

void Brain::ChangeCamera(const std::string& request_name)
{
	now_camera_ = request_name;
}

void Brain::CollisionNotActive()
{

}

void Brain::CollisionActive()
{

}

const VECTOR Brain::GetVelocity() const
{
	return vel_;
}

const VECTOR Brain::GetTargetVelocity() const
{
	return target_vel_;
}

Brain::Brain()
	: vel_(VectorAssistant::VGetZero())
	, target_vel_(VectorAssistant::VGetZero())
	, can_hit_(TRUE)
{

}