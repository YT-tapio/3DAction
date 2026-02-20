#include"DxLib.h"
#include"tracking_camera.h"
#include"vector_assistant.h"

TrackingCamera::TrackingCamera(VECTOR* pos)
	: tracking_object_pos_(pos)
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

void TrackingCamera::Update()
{
	// ‚Æ‚è‚ ‚¦‚¸’Ç‚¢‚©‚¯‚é‚æ‚¤‚É‚µ‚Ü‚µ‚å‚¤‚©
	vel_ = VectorAssistant::VGetZero();

	vel_ = VGet(0.f, 0.f, 1.f);

	target_vel_ = vel_;
}