#include<memory>
#include<string>
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"camera.h"
#include"radian_assistant.h"
#include"vector_assistant.h"
#include"color.h"
#include"debug.h"
#include<functional>
#include"brain.h"
#include"rigid_body.h"
#include"sphere.h"
#include"physics.h"

Camera::Camera(const VECTOR& pos,const VECTOR& target_pos,const bool& is_physics)
	: rigid_body_(nullptr)
{
	const float kRad		= 75.f;
	near_					= 0.1f;
	far_					= 1000.f;
	fov_					= kRad;
	pos_					= pos;
	//pos_ = VGet(6,-1.f,-8.5f);
	vel_					= VectorAssistant::VGetZero();
	target_vel_		= VectorAssistant::VGetZero();
	target_pos_		= target_pos;
	is_physics_ = is_physics;
	if (is_physics_)
	{
		rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Sphere>(1.f, VectorAssistant::VGetZero()), &pos_, FALSE, FALSE, 0.1f, 1.f);
	}
	
	Setting();
}

Camera::~Camera()
{

}

void Camera::Init()
{
	// pysicsÇ÷ÇÃìoò^
	if (rigid_body_ != nullptr)
	{
		rigid_body_->Init(weak_from_this());
		rigid_body_->SetTag("camera");
		Physics::GetInstance().AddBody(rigid_body_);
	}
}

void Camera::Update()
{
	VECTOR dir	= VectorAssistant::VGetZero();
	VECTOR target_dir = VectorAssistant::VGetZero();

	// brainÇ©ÇÁÇÃà⁄ìÆílÇéÛÇØéÊÇÈ
	vel_				= Brain::GetInstance().GetVelocity();
	target_vel_	= Brain::GetInstance().GetTargetVelocity();
	auto zoom_value = Brain::GetInstance().GetZoomValue();
	fov_ = fov_ + zoom_value;
	if (rigid_body_ != nullptr)
	{
		rigid_body_->SetTargetVelocity(vel_);
	}
	Setting();
	Brain::GetInstance().SetCurrentFov(fov_);
	// ÉäÉXÉiÅ[ÇÃê›íË
	Set3DSoundListenerPosAndFrontPos_UpVecY(pos_, target_pos_);
}

void Camera::Debug()
{
	DrawSphere3D(target_pos_, 1.f, 20.f, Color::kWhite, Color::kWhite, TRUE);
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "------------camera----------", Color::kWhite);
	Debug::GetInstance().Add();
	
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----pos-----", Color::kWhite);
	Debug::GetInstance().Add();
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "x : %.2f,y : %.2f,z : %.2f", pos_.x, pos_.y, pos_.z);
	Debug::GetInstance().Add();

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----target_pos-----", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(target_pos_);

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "-----dir-----", Color::kWhite);
	Debug::GetInstance().Add();
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "x : %.2f,y : %.2f,z : %.2f", dir_.x, dir_.y, dir_.z);
	Debug::GetInstance().Add();
}

void Camera::Setting()
{
	if (!is_physics_)
	{
		pos_ = VAdd(pos_, vel_);
	}
	target_pos_ = VAdd(target_pos_, target_vel_);

	SetCameraNearFar(near_, far_);
	auto fov = RadianAssistant::TheNumRadian(fov_);
	SetupCamera_Perspective(fov);
	//printfDx("fov:%.2f\n",fov_);
	SetCameraPositionAndTarget_UpVecY(pos_, target_pos_);
	Effekseer_Sync3DSetting();
	dir_ = VectorAssistant::VGetDir(pos_, target_pos_);
}

void Camera::OnHit(std::shared_ptr<IPhysicsEventReceiver> obj)
{
	//printfDx("aa\n");
}

VECTOR* Camera::GetPos()
{
	return &pos_;
}

VECTOR* Camera::GetTargetPos()
{
	return &target_pos_;
}

std::shared_ptr<RigidBody> Camera::GetRigidBody()
{
	return rigid_body_;
}