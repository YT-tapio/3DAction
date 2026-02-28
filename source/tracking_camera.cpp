#include"DxLib.h"
#include"tracking_camera.h"
#include"vector_assistant.h"

TrackingCamera::TrackingCamera(VECTOR* tracking_pos, VECTOR* camera_pos, VECTOR* target_pos)
	: VirtualCameraBase(camera_pos, target_pos)
	, tracking_object_pos_(tracking_pos)
{
	tracking_obj_to_camera_dist_ = VectorAssistant::VGetZero();
}

TrackingCamera::~TrackingCamera()
{

}

void TrackingCamera::Init()
{
	// tracking_object_pos
	tracking_obj_to_camera_dist_ = VSub(*pos_, *tracking_object_pos_);
}

void TrackingCamera::Update()
{
	// ‚Æ‚è‚ ‚¦‚¸’Ç‚¢‚©‚¯‚é‚æ‚¤‚É‚µ‚Ü‚µ‚å‚¤‚©
	vel_ = VectorAssistant::VGetZero();

	// init‚Å’è‚ß‚½‚Æ‚±‚ë‚É”z’u

	VECTOR camera_to_target_dir = VectorAssistant::VGetDir(*pos_, *target_pos_);
	VECTOR camera_to_tracking_object_dir = VectorAssistant::VGetDir(*pos_, *tracking_object_pos_);

	float rad = VectorAssistant::GetTwoVectorRad(camera_to_target_dir, camera_to_tracking_object_dir);

	// ‚±‚ÌŠp“x‚ª‚Ç‚ê‚®‚ç‚¢‚©‚É‚æ‚Á‚Ä‘¬‚³‚ª•Ï‚í‚é
	
	VECTOR next_pos = VAdd(*tracking_object_pos_, tracking_obj_to_camera_dist_);
	vel_ = VSub(next_pos,*pos_);
	target_vel_ = vel_;
	printfDx("x : %.2f,y : %.2f,z : %.2f\n", tracking_obj_to_camera_dist_.x, tracking_obj_to_camera_dist_.y, tracking_obj_to_camera_dist_.z);
}