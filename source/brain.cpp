
#include"DxLib.h"
#include"brain.h"
#include"vector_assistant.h"
#include"tracking_camera.h"
#include"player.h"

void Brain::Init()
{

}

void Brain::CreatePlaySceneVirtualCamera(std::shared_ptr<Player> player,VECTOR* camera_pos, VECTOR* target_pos)
{
	virtual_cameras_[kTracking] = std::make_shared<TrackingCamera>(player->GetHeadPos(), camera_pos, target_pos);
}

void Brain::Update()
{
	// カメラのupdateと切り替え
	// 切り替え
	// 現在のシーンを見て切り替えのチェンジ
	// VirtualCameraのupdate
	virtual_cameras_[kTracking]->Update();
	
	vel_				= virtual_cameras_[kTracking]->GetVelocity();
	target_vel_	= virtual_cameras_[kTracking]->GetTargetVelocity();
}


void Brain::DeleteVirtualCamera()
{
	virtual_cameras_.clear();
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
{

}