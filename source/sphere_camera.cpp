#include<memory>
#include"DxLib.h"
#include"sphere_camera.h"
#include"input_base.h"
#include"input_manager.h"
#include"vector_assistant.h"

SphereCamera::SphereCamera(VECTOR* center_pos,VECTOR* pos, VECTOR* target_pos)
	:VirtualCameraBase(pos,target_pos)
{
	center_pos_ = center_pos;
	rotation_ = VectorAssistant::VGetZero();
	input_ = InputManager::GetInstance().GetPlayerInput();
}

SphereCamera::~SphereCamera()
{

}

void SphereCamera::Init()
{
	VECTOR target_pos_to_camera_dist	= VSub(*target_pos_, *pos_);
	VECTOR target_pos_to_camera_dir		= VNorm(target_pos_to_camera_dist);



}

void SphereCamera::Update()
{
	// target_posを中心とし回転をさせる
	VECTOR input_value = VectorAssistant::VGetZero();
	// playerの入力が必要
	// 入力値をもらう
	
	input_value = input_->GetCameraDir();

	printfDx("x : %.2f,y : %.2f,z : %.2f\n", input_value.x, input_value.y, input_value.z);
	
	vel_ = input_value;
}

