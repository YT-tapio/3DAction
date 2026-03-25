#include<iostream>
#include<map>
#include<vector>
#include"DxLib.h"
#include"player.h"
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
#include"enemy_base.h"
#include"behavior_base.h"
#include"punch.h"
#include"check_my_area.h"
#include"skill_base.h"
#include"punch_skill.h"

Player::Player(VECTOR* camera_dir,std::shared_ptr<const InputBase> input)
	: CharacterBase("player")
	, IPhysicsEventReceiver()
{
	camera_dir_ = camera_dir;
	hand_pos_ = VectorAssistant::VGetZero();
	vel_		= VectorAssistant::VGetZero();
	dir_		= VectorAssistant::VGetZero();
	attack_target_pos_ = VectorAssistant::VGetZero();
	pos_		= VGet(0.f, -2.f,10.f);
	VECTOR head_pos = VAdd(pos_, VGet(0.f, 10.f, 0.f));
	head_pos_ = head_pos;
	
	scale_ = VectorAssistant::VGetSame(0.05f);
	handle_ = MV1LoadModel("data/model/player/Lola_B_Styperek.mv1");
	
	if (handle_ == -1) { printfDx("“Ç‚İ‚İƒGƒ‰[\n"); }
	Setting();
	UpdateBone();
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(1.5f, 6.f, VectorAssistant::VGetZero()), &pos_, TRUE, FALSE, 1.f);
	fall_speed_ = 0.f;
	is_move_ = FALSE;
	is_ground_ = FALSE;
	is_dash_ = FALSE;
	is_attack_target_in_range_ = FALSE;
	is_stop_ = FALSE;
	input_ = input;
	target_rot_y_ = 0;
	
}

Player::~Player()
{

}

void Player::Init()
{
	auto mine = std::dynamic_pointer_cast<Player>(shared_from_this());
	auto mine_object = std::dynamic_pointer_cast<ObjectBase>(mine);
	
	if (mine_object == nullptr) { printfDx("¸”s"); }

	behavior_ = std::make_shared<Punch>(mine_object, &hand_pos_, std::make_shared<RigidBody>(std::make_shared<Sphere>(1.5f, VGet(0.f, 0.f, 0.f)), &hand_pos_, FALSE, TRUE, 1.f));
	rigid_body_->Init(weak_from_this());
	my_area_ = std::make_shared<CheckMyArea>(std::make_shared<Sphere>(20.f, VectorAssistant::VGetZero()), &pos_);
	skill_ = std::make_shared<PunchSkill>(mine, &hand_pos_, 1.5f);
	// physics‚Ì“o˜^
	Physics::GetInstance().AddBody(rigid_body_);
	// setter‚Ö‚Ì“o˜^
	ObjectSetter::GetInstance().AddResource(handle_, &pos_,&rot_,&scale_);
	
	animator_ = std::make_shared<AnimatorPlayer>(handle_, mine);
	animator_->Init();
	behavior_->Init();
	my_area_->Init();
	skill_->Init();
}

void Player::Update()
{
	// input_->Update();
	Move();
	//behavior_->Update();
	
	//VECTOR a = *head_pos_;
	//printfDx("x : %.2f,y : %.2f,z : %.2f\n", (*head_pos_).x, (*head_pos_).y, (*head_pos_).z);
	//Gravity();
	rigid_body_->SetTargetVelocity(vel_);
	animator_->Update();
	Setting();
	// QÆ‚ÌXV
	UpdateBone();
}

void Player::LateUpdate()
{
	head_pos_ = VAdd(pos_, VGet(0.f, 10.f, 0.f));
}

void Player::SetVelocity(const VECTOR& velocity)
{
	vel_ = velocity;
}

void Player::SetIsStop(bool flag)
{
	is_stop_ = flag;
}

void Player::Draw()
{
	MV1DrawModel(handle_);
}

void Player::Debug()
{
	rigid_body_->Debug();
	// behavior_->Debug();
	my_area_->Debug();
	skill_->Debug();
	
	// DrawSphere3D(attack_target_pos_, 3.f, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	//DrawSphere3D(head_pos_, 0.5f, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
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

	VECTOR dir = VectorAssistant::VGetZero();
	//dir_ = VectorAssistant::VGetZero();
	vel_ = VectorAssistant::VGetZero();
	float speed = kSpeed;

	if (animator_->GetNowAnimName() != "punch")
	{
		dir.x = input_->GetMoveDir().x;
		dir.z = input_->GetMoveDir().y;
	}

	if (VSize(dir) > 0 && !is_stop_)
	{
		dir_ = VectorAssistant::VGetRotPiY(VectorAssistant::VGetFlat(*camera_dir_), VectorAssistant::VGetTan(dir));
		dir_ = VNorm(dir_);
		
		if (input_->IsDash())
		{
			speed *= 2.5f;
			is_dash_ = TRUE;
		}
		else
		{
			is_dash_ = FALSE;
		}
		is_move_ = TRUE;
		vel_ = VScale(dir_, speed);
	}
	else
	{
		is_move_ = FALSE;
		is_dash_ = FALSE;
	}
	/*
	if (VSize(dir) > 0)
	{
		vel_ = VScale(dir_, speed);
	}
	*/

	/*
	if (animator_->GetPlayTime("punch") == 0.f)
	{
		
	}
	else
	{
		DecideAttackTarget();
		if (is_attack_target_in_range_)
		{
			dir_ = VNorm(VSub(attack_target_pos_, pos_));
			vel_ = dir_;
		}
		else
		{
			vel_ = VectorAssistant::VGetZero();
		}
	}
	*/
	
	skill_->Update();
	
	if (!is_ground_)
	{
		fall_speed_ += 0.03f;
	}

	vel_ = VAdd(vel_, VGet(0.f, -fall_speed_, 0.f));
	vel_ = VScale(vel_, (FPS::GetInstance().GetDeltaTime() * 60.f));
	if (VSize(vel_) > 0.f)
	{ 
		dir_ = VNorm(vel_);
		target_rot_y_ = atan2f(-dir_.x, (-dir_.z));
	}
	// printfDx("x : %.2f,y : %.2f,z : %.2f\n", vel_.x, vel_.y, vel_.z);
	rot_.y = RadianAssistant::Lerp(rot_.y, target_rot_y_, RadianAssistant::kOneRad * 15.f * FPS::GetInstance().GetDeltaTime() * 60.f);
	if (CheckHitKey(KEY_INPUT_SPACE)) { pos_ = VGet(0.f, 0.f, 0.f); vel_ = VGet(0.f, 0.f, 0.f); is_ground_ = FALSE; fall_speed_ = 0.f;}
}

void Player::Gravity()
{
	if (is_ground_) { return; }
	rigid_body_->AddForce();
}

void Player::UpdateBone()
{
	int hand_bone_num = 0;
	const TCHAR* hand_bone_path = "mixamorig:RightHand";
	hand_bone_num = MV1SearchFrame(handle_, hand_bone_path);
	MATRIX hand_mat = MV1GetFrameLocalWorldMatrix(handle_, hand_bone_num);
	VECTOR hand_pos = VectorAssistant::VGetPositionFromMatrix(hand_mat);
	hand_pos_ = hand_pos;
}

void Player::DecideAttackTarget()
{
	// UŒ‚‘ÎÛ‚ª”ÍˆÍ“à‚É‚¢‚È‚¢‚È‚ç‚â‚ß‚é
	attack_target_pos_ = VectorAssistant::VGetZero();
	is_attack_target_in_range_ = FALSE;
	if (my_area_->GetMyAreaObject().size() == 0)
	{
		return;
	}
	
	
	// enemy‚Ì’†‚©‚ç‹ß‚¢“G‚ğUŒ‚‘ÎÛ‚É“®‚­
	int enemy_num = 0;
	std::map<float, VECTOR> dist_pos_mp;

	for (const auto my_area_objects : my_area_->GetMyAreaObject())
	{
		std::shared_ptr<EnemyBase> enemy = std::dynamic_pointer_cast<EnemyBase>(my_area_objects.lock());
		if (enemy != nullptr)
		{
			enemy_num++;
			is_attack_target_in_range_ = TRUE;
			VECTOR enemy_pos = enemy->GetPosition();
			float dist_size = VSize(VSub(enemy_pos, pos_));
			dist_pos_mp[dist_size] = enemy_pos;
		}
	}
	if (enemy_num == 0) { return; }
	
	if (dist_pos_mp.size() > 0)
	{
		auto most_near_pos = dist_pos_mp.begin()->second;
		attack_target_pos_ = most_near_pos;
		
	}
}

void Player::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	//‰½‚©‚ª“–‚½‚Á‚½‚Ìˆ—

	// ihit‚ğ‰½Ò‚©‚É•ÏŠ·
	auto stage = std::dynamic_pointer_cast<Stage>(object);
	auto enemy = std::dynamic_pointer_cast<EnemyBase>(object);
	auto punch = std::dynamic_pointer_cast<Punch>(object);
	if (stage != nullptr)
	{
		//printfDx("stage");
		return;
	}

	if (enemy != nullptr)
	{
		//printfDx("enemy");
		return;
	}

	if (punch != nullptr)
	{
		// ©g‚ÆƒI[ƒi[‚Ìƒpƒ“ƒ`‚ªplayer‚Écast‚µ‚Änullptr‚È‚Á‚½‚çˆ—‚·‚é
		if (std::dynamic_pointer_cast<Player>(punch->GetOwner().lock()) == nullptr)
		{
			animator_->PlayRequest("on_damage");
		}
		return;
	}

}

void Player::OnGrounded(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto check_area = std::dynamic_pointer_cast<CheckMyArea>(object);

	if (check_area != nullptr) { return; }

	is_ground_ = TRUE;
	fall_speed_ = 0.f;
}

void Player::OnUnGrounded(std::shared_ptr<IPhysicsEventReceiver> object)
{
	is_ground_ = FALSE;
	// printfDx("1\n");
}

std::vector<std::weak_ptr<ObjectBase>> Player::GetMyAreaObject()
{
	return my_area_->GetMyAreaObject();
}

VECTOR* Player::GetHeadPos()
{
	return &head_pos_;
}

const std::shared_ptr<const InputBase> Player::GetInput() const
{
	return input_;
}

const bool Player::GetIsMove() const
{
	return is_move_;
}

const bool Player::GetIsGround() const
{
	return is_ground_;
}

const bool Player::GetIsDash() const
{
	return is_dash_;
}