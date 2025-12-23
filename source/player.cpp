#include<iostream>
#include"DxLib.h"
#include"player.h"
#include"collider_base.h"
#include"capsule.h"
#include"rigid_body.h"
#include"FPS.h"
#include"vector_assistant.h"
#include"Debug.h"
#include"color.h"
#include"physics.h"
#include"stage.h"

Player::Player(VECTOR* camera_dir)
	: CharacterBase("player")
	, IHit()
{
	camera_dir_ = camera_dir;
	vel_		= VectorAssistant::VGetZero();
	dir_		= VectorAssistant::VGetZero();
	pos_		= VGet(0.f, 0.f, 30.f);
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(5.f,10.f), &pos_);
}

Player::~Player()
{

}

void Player::Init()
{
	rigid_body_->Init(weak_from_this());
	// physics‚Ì“o˜^
	Physics::GetInstance().AddBody(rigid_body_);
}

void Player::Update()
{
	Move();

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
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "x : %.2f, y : %.2f, z : %.2f", pos_.x, pos_.y, pos_.z);
	Debug::GetInstance().Add();

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "dir", Color::kWhite);
	Debug::GetInstance().Add();
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "x : %.2f, y : %.2f, z : %.2f", dir_.x, dir_.y, dir_.z);
	Debug::GetInstance().Add();

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "camera_dir", Color::kWhite);
	Debug::GetInstance().Add();
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "x : %.2f, y : %.2f, z : %.2f", camera_dir_->x, camera_dir_->y, camera_dir_->z);
	Debug::GetInstance().Add();

}

void Player::LoadFile()
{
	
}

void Player::Move()
{
	//Input‚ğì‚Á‚½‚ç‚±‚Ìˆ—‚ÍÁ‚µ‚Ä‚­‚¾‚³‚¢
	dir_ = VectorAssistant::VGetZero();
	
	if (CheckHitKey(KEY_INPUT_W)) { dir_ = VAdd(dir_, VGet(0.f, 0.f, 1.f));  }
	if (CheckHitKey(KEY_INPUT_S)) { dir_ = VAdd(dir_, VGet(0.f, 0.f, -1.f)); }
	if (CheckHitKey(KEY_INPUT_D)) { dir_ = VAdd(dir_, VGet(1.f, 0.f, 0.f));  }
	if (CheckHitKey(KEY_INPUT_A)) { dir_ = VAdd(dir_, VGet(-1.f, 0.f, 0.f)); }

	if (VSize(dir_) > 0) 
	{
		float constant = VectorAssistant::VGetTan(*camera_dir_);
		dir_ = VScale(dir_, constant);
		dir_ = VNorm(dir_);
	}

	vel_ = VScale(dir_, kSpeed);
	vel_ = VScale(vel_, (FPS::GetInstance().GetDeltaTime() * 60));

	pos_ = VAdd(pos_, vel_);

}

void Player::OnHit(std::shared_ptr<IHit> object)
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