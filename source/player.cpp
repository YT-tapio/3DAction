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
#include"input_base.h"
#include"player_input.h"
#include"ai_input.h"
#include"animator_base.h"
#include"animator_player.h"

Player::Player(VECTOR* camera_dir,std::shared_ptr<const InputBase> input)
	: CharacterBase("player")
	, IPhysicsEventReceiver()
{
	camera_dir_ = camera_dir;
	vel_		= VectorAssistant::VGetZero();
	dir_		= VectorAssistant::VGetZero();
	pos_		= VGet(0.f, -2.f,10.f);
	VECTOR head_pos = VAdd(pos_, VGet(0.f, 10.f, 0.f));
	head_pos_ = head_pos;
	printfDx("x : %.2f,y : %.2f,z : %.2f\n", head_pos_.x, head_pos_.y, head_pos_.z);
	scale_ = VectorAssistant::VGetSame(0.05f);
	handle_ = MV1LoadModel("data/model/player/Lola_B_Styperek.mv1");
	if (handle_ == -1) { printfDx("ì«Ç›çûÇ›ÉGÉâÅ[\n"); }
	Setting();
	if (TRUE)
	{
		rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(1.5f, 6.f, VectorAssistant::VGetZero()), &pos_, TRUE, FALSE, 1.f);
	}
	else
	{
		rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Sphere>(1.5f, VectorAssistant::VGetZero()), &pos_, TRUE, FALSE, 1.f);
	}
	fall_speed_ = 0.f;
	is_ground_ = FALSE;
	input_ = input;
	animator_ = std::make_shared<AnimatorPlayer>(handle_);
	animator_->Init();
}

Player::~Player()
{

}

void Player::Init()
{
	rigid_body_->Init(weak_from_this());
	// physicsÇÃìoò^
	Physics::GetInstance().AddBody(rigid_body_);
	// setterÇ÷ÇÃìoò^
	ObjectSetter::GetInstance().AddResource(handle_, &pos_,&rot_,&scale_);
}

void Player::Update()
{
	// input_->Update();
	Move();

	rigid_body_->SetVelocity(vel_);
	//VECTOR a = *head_pos_;
	//printfDx("x : %.2f,y : %.2f,z : %.2f\n", (*head_pos_).x, (*head_pos_).y, (*head_pos_).z);
	//Gravity();
	animator_->Update();
	Setting();
}

void Player::LateUpdate()
{
	head_pos_ = VAdd(pos_, VGet(0.f, 10.f, 0.f));
}

void Player::Draw()
{
	MV1DrawModel(handle_);
}

void Player::Debug()
{
	rigid_body_->Debug();
	DrawSphere3D(head_pos_, 0.5f, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "----------player-----------", Color::kWhite);
	Debug::GetInstance().Add();

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "pos", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(pos_);
	Debug::GetInstance().DrawVector(head_pos_);

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
	//std::shared_ptr<const InputBase> input = input_;
	
	VECTOR dir = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();

	float speed = kSpeed;

	//InputÇçÏÇ¡ÇΩÇÁÇ±ÇÃèàóùÇÕè¡ÇµÇƒÇ≠ÇæÇ≥Ç¢
	if (CheckHitKey(KEY_INPUT_W)) { dir = VAdd(dir, VGet(0.f, 0.f, 1.f));  }
	if (CheckHitKey(KEY_INPUT_S)) { dir = VAdd(dir, VGet(0.f, 0.f, -1.f)); }
	if (CheckHitKey(KEY_INPUT_D)) { dir = VAdd(dir, VGet(1.f, 0.f, 0.f));  }
	if (CheckHitKey(KEY_INPUT_A)) { dir = VAdd(dir, VGet(-1.f, 0.f, 0.f)); }

	dir = input_->GetMoveDir();
	if (input_->IsDash()) { speed *= 2.5f; }
	if (VSize(dir) > 0) 
	{
		dir_ = VectorAssistant::VGetRotPiY(VectorAssistant::VGetFlat(*camera_dir_), VectorAssistant::VGetTan(dir));
		dir_ = VNorm(dir_);
	}

	vel_ = VScale(dir_, speed);
	if (!is_ground_)
	{
		fall_speed_ += 0.05f;
		vel_ = VAdd(vel_, VGet(0.f, -fall_speed_, 0.f));
	}
	
	vel_ = VScale(vel_, (FPS::GetInstance().GetDeltaTime() * 60.f));
	if (VSize(vel_) > 0.f)
	{ 
		rot_.y = atan2f(-dir_.x, (-dir_.z));
		//printfDx("%.2f\n", rot_.y);
		if (rot_.y > RadianAssistant::kReverceRad)	{ rot_.y -= (RadianAssistant::kReverceRad * 2.f); }
		if (rot_.y < -RadianAssistant::kReverceRad)	{ rot_.y += (RadianAssistant::kReverceRad * 2.f); }
	}
	
	if (CheckHitKey(KEY_INPUT_SPACE)) { pos_ = VGet(0.f, 0.f, 0.f); vel_ = VGet(0.f, 0.f, 0.f); is_ground_ = FALSE; fall_speed_ = 0.f;}
	
}

void Player::Gravity()
{
	if (is_ground_) { return; }
	rigid_body_->AddForce();
}

void Player::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	//âΩÇ©Ç™ìñÇΩÇ¡ÇΩéûÇÃèàóù

	// ihitÇâΩé“Ç©Ç…ïœä∑

	auto stage = std::dynamic_pointer_cast<Stage>(object);

	if (stage != nullptr)
	{
		//printfDx("stage");
		return;
	}

}

void Player::OnGrounded()
{
	is_ground_ = TRUE;
	fall_speed_ = 0.f;
	// printfDx("is_ground\n");
}

void Player::OnUnGrounded()
{
	is_ground_ = FALSE;
	// printfDx("1\n");
}

VECTOR* Player::GetHeadPos()
{
	return &head_pos_;
}