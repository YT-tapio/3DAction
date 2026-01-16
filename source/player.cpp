#include<iostream>
#include"DxLib.h"
#include"player.h"
#include"collider_base.h"
#include"capsule.h"
#include"sphere.h"
#include"rigid_body.h"
#include"FPS.h"
#include"vector_assistant.h"
#include"Debug.h"
#include"color.h"
#include"physics.h"
#include"object_setter.h"
#include"stage.h"

Player::Player(VECTOR* camera_dir)
	: CharacterBase("player")
	, IPhysicsEventReceiver()
{
	camera_dir_ = camera_dir;
	vel_		= VectorAssistant::VGetZero();
	dir_		= VectorAssistant::VGetZero();
	pos_		= VGet(0.f, -2.f,10.f);
	scale_ = VectorAssistant::VGetSame(0.05f);
	handle_ = MV1LoadModel("data/model/player/Lola_B_Styperek.mv1");
	if (handle_ == -1) { printfDx("“Ç‚İ‚İƒGƒ‰[\n"); }
	Setting();
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(5.f, 10.f, VectorAssistant::VGetZero()), &pos_, TRUE, FALSE, 1.f);
}

Player::~Player()
{

}

void Player::Init()
{
	rigid_body_->Init(weak_from_this());
	// physics‚Ì“o˜^
	Physics::GetInstance().AddBody(rigid_body_);
	// setter‚Ö‚Ì“o˜^
	ObjectSetter::GetInstance().AddResource(handle_, &pos_,&rot_,&scale_);
}

void Player::Update()
{
	Move();

	rigid_body_->Update(vel_);
	Setting();
}

void Player::Draw()
{
	MV1DrawModel(handle_);
}

void Player::Debug()
{
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "----------player-----------", Color::kWhite);
	Debug::GetInstance().Add();

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "pos", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(pos_);

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "dir", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(dir_);

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "vel", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(vel_);

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "camera_dir", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(*camera_dir_);

}

void Player::LoadFile()
{
	
}

void Player::Move()
{
	VECTOR dir = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();

	//Input‚ğì‚Á‚½‚ç‚±‚Ìˆ—‚ÍÁ‚µ‚Ä‚­‚¾‚³‚¢
	if (CheckHitKey(KEY_INPUT_W)) { dir = VAdd(dir, VGet(0.f, 0.f, 1.f));  }
	if (CheckHitKey(KEY_INPUT_S)) { dir = VAdd(dir, VGet(0.f, 0.f, -1.f)); }
	if (CheckHitKey(KEY_INPUT_D)) { dir = VAdd(dir, VGet(1.f, 0.f, 0.f));  }
	if (CheckHitKey(KEY_INPUT_A)) { dir = VAdd(dir, VGet(-1.f, 0.f, 0.f)); }

	if (VSize(dir) > 0) 
	{
		dir_ = VectorAssistant::VGetRotPiY(VectorAssistant::VGetFlat(*camera_dir_), VectorAssistant::VGetTan(dir));
	}

	vel_ = VScale(dir_, kSpeed);
	vel_ = VScale(vel_, (FPS::GetInstance().GetDeltaTime() * 60));

	//pos_ = VAdd(pos_, vel_);

}

void Player::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	//‰½‚©‚ª“–‚½‚Á‚½‚Ìˆ—

	// ihit‚ğ‰½Ò‚©‚É•ÏŠ·

	auto stage = std::dynamic_pointer_cast<Stage>(object);

	if (stage != nullptr)
	{
		//printfDx("stage");
		return;
	}

}

void Player::OnGrounded()
{

}

void Player::OnUnGrounded()
{

}