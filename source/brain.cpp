#include<unordered_map>
#include<string>
#include<memory>
#include"DxLib.h"
#include"brain.h"
#include"vector_assistant.h"
#include"tracking_camera.h"

Brain::Brain()
	: vel_			(VectorAssistant::VGetZero())
	, target_vel_	(VectorAssistant::VGetZero())
	, kTracking("tracking")
{
	// バーチャルカメラを生成
	virtual_cameras_[kTracking] = std::make_shared<TrackingCamera>();
}

Brain::~Brain()
{

}

void Brain::Init()
{

}

void Brain::Update()
{
	// カメラのupdateと切り替え
	// 切り替え
	// VirtualCameraのupdate
	virtual_cameras_[kTracking]->Update();
}