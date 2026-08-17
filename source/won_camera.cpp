#include<functional>
#include<memory>
#include"DxLib.h"
#include"won_camera.h"
#include"lerp.h"
#include"fps.h"
#include"condition_timer.h"
#include<unordered_map>
#include"brain.h"

WonCamera::WonCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos, std::function<VECTOR()> enemy_center_pos, std::function<VECTOR()> enemy_dir)
	: VirtualCameraBase(main_camera_pos, main_camera_target_pos)
	, enemy_center_pos_(enemy_center_pos)
	, enemy_dir_(enemy_dir)
	, offset_(VGet(0.f, 10.f, 0.f))
	, future_pos_(VectorAssistant::VGetZero())
{
	timer_ = std::make_shared<ConditionTimer>(3.f);
}

WonCamera::~WonCamera()
{

}

void WonCamera::Init()
{
	// “G‚Ì³–Ê‚ÖˆÚ“®
	//printfDx("x:%.2f,y:%.2f,z:%.2f\n", future_pos_.x, future_pos_.y, future_pos_.z);
	VECTOR enemy_dir = enemy_dir_();
	future_pos_ = VScale(enemy_dir, kPlayerToEnemyDistSize);
	auto enemy_center_pos = enemy_center_pos_();
	future_pos_ = VAdd(future_pos_, enemy_center_pos);
	//printfDx("x:%.2f,y:%.2f,z:%.2f\n", future_pos_.x, future_pos_.y, future_pos_.z);
	future_pos_ = VAdd(future_pos_, offset_);
	printfDx("x:%.2f,y:%.2f,z:%.2f\n", future_pos_.x, future_pos_.y, future_pos_.z);
	vel_ = VectorAssistant::VGetZero();
	timer_->ReStart();
}

void WonCamera::Update()
{
	float camera_speed = 1.3f * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS();
	float camera_target_speed = 1.f * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS();
	VECTOR main_camera_pos = *main_camera_pos_;
	VECTOR enemy_center_pos = enemy_center_pos_();
	VECTOR main_camera_target_pos = *main_camera_target_pos_;
	vel_ = VSub(Lerp::LerpV(main_camera_pos , future_pos_, camera_speed), main_camera_pos);
	// “G‚Ì’†S“_‚ª^‚ñ’†
	target_vel_ = VSub(Lerp::LerpV(enemy_center_pos, main_camera_target_pos, camera_target_speed),main_camera_target_pos);
	timer_->Update();
	// ŽžŠÔ‚ª‚½‚Ä‚Î‚à‚Æ‚à‚Æ‚ÌƒJƒƒ‰‚É–ß‚é
	if (timer_->GetIsEnd())
	{
		Brain::GetInstance().ChangeCamera("Sphere");
	}
}