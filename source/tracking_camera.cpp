#include"DxLib.h"
#include"tracking_camera.h"
#include"vector_assistant.h"

TrackingCamera::TrackingCamera(VECTOR* pos)
	: player_head_pos_(pos)
{

}

TrackingCamera::~TrackingCamera()
{

}

void TrackingCamera::Init(const VECTOR& camera_pos, const VECTOR& target_pos)
{
	pos_		= camera_pos;
	target_pos_ = target_pos;
}

VECTOR TrackingCamera::Update()
{
	vel_ = VectorAssistant::VGetZero();


	return vel_;
}