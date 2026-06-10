#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<functional>
#include"DxLib.h"
#include"player.h"
#include"capsule.h"
#include"sphere.h"
#include"rigid_body.h"
#include"FPS.h"
#include"vector_assistant.h"
#include"radian_assistant.h"
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
#include"avoid_skill.h"
#include"area_heal_skill.h"
#include"area_heal_give_player.h"
#include"skill_name.h"
#include"skill_loader.h"
#include"csv_file_assistant.h"
#include"input_manager.h"
#include"attack_base.h"
#include"double_punch.h"
#include"status.h"
#include"status_container.h"
#include"buff_type.h"
#include"attack_type.h"
#include"effect_manager.h"
#include"effect_id.h"
#include"effect_end_state.h"
#include"player_ui_group.h"

Player::Player(VECTOR* camera_dir,std::shared_ptr<const InputBase> input,const std::string name)
	: CharacterBase("player")
	, IPhysicsEventReceiver()
	, name_(name)
	, input_(input)
{
	
	camera_dir_ = camera_dir;
	right_hand_pos_ = VectorAssistant::VGetZero();
	left_hand_pos_ = VectorAssistant::VGetZero();
	vel_		= VectorAssistant::VGetZero();
	dir_		= VectorAssistant::VGetZero();
	attack_target_pos_ = VectorAssistant::VGetZero();
	pos_		= VectorAssistant::VGetZero();
	rot_ = VectorAssistant::VGetZero();
	VECTOR head_pos = VAdd(pos_, VGet(0.f, 10.f, 0.f));
	head_pos_ = head_pos;

	skill1_id_ = SkillName::kNothing;
	skill2_id_ = SkillName::kNothing;

	scale_ = VectorAssistant::VGetSame(0.05f);
	handle_ = -1;
	Setting();
	UpdateBone();
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(1.5f, 6.f, VectorAssistant::VGetZero()), 
		&pos_, TRUE, FALSE, 0.03f, 0.1f);
	VECTOR hp_pos = VectorAssistant::VGet2D(300.f, 800.f);
	VECTOR hp_size = VectorAssistant::VGet2D(100.f, 30.f);
	status_container_ = std::make_shared<StatusContainer>(name_,hp_pos, hp_size);
	fall_speed_ = 0.f;
	is_move_ = FALSE;
	is_dash_ = FALSE;
	is_attack_target_in_range_ = FALSE;
	is_stop_ = FALSE;
	can_move_ = TRUE;
	on_damage_ = FALSE;
	//input_ = input;
	target_rot_y_ = 0;
	speed_ = 0.f;
}

Player::~Player()
{
	
}

void Player::Init()
{
	auto mine = std::dynamic_pointer_cast<Player>(shared_from_this());
	auto mine_object = std::dynamic_pointer_cast<ObjectBase>(mine);
	auto input_change = std::dynamic_pointer_cast<IInputChange>(mine);
	if (mine_object == nullptr) { printfDx("失敗"); }
	if (input_change == nullptr) { printfDx("失敗です"); }
	// 検知用範囲
	detection_radius_ = 25.f;

	LoadFile("",name_);
	MakeSkill(mine);
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("player");
	my_area_ = std::make_shared<CheckMyArea>(std::make_shared<Sphere>(detection_radius_, VectorAssistant::VGetZero()), &pos_);
	//skill_ = std::make_shared<PunchSkill>(mine, &hand_pos_, 1.5f, detection_radius);
	//skill_			= std::make_shared<PunchSkill>(mine, &hand_pos_, 1.5f, detection_radius_);
	//second_skill_	= std::make_shared<AreaHealSkill>(mine,&pos_,5.f);
	
	//avoid_ = std::make_shared<AvoidSkill>(mine);
	test_behavior_ = 
		std::make_shared<AreaHealGivePlayer>(mine,
			std::make_shared<CheckMyArea>(std::make_shared<Sphere>(20.f,
				VectorAssistant::VGetZero()), &pos_), &pos_);
	is_invincible_ = FALSE;
	can_move_ = TRUE;
	on_damage_ = FALSE;
	InputManager::GetInstance().AddInput(input_change);
	// physicsの登録
	Physics::GetInstance().AddBody(rigid_body_);
	// setterへの登録
	ObjectSetter::GetInstance().AddResource(handle_, &pos_,&rot_,&scale_);
	
	std::function<int()> get_base_hp = [this]() -> int
		{
			return static_cast<int>(status_container_->GetBaseStatus().hp);
		};
	std::function<int()> get_current_hp = [this]() -> int
		{
			return static_cast<int>(status_container_->GetCurrentStatus().hp);
		};

	// ui表示
	PlayerUIGroup::GetInstance().MakeHPUI(get_base_hp, get_current_hp);

	target_rot_y_ = rot_.y;

	animator_ = std::make_shared<AnimatorPlayer>(handle_, name_);
	animator_->Init();
	my_area_->Init();

	if (skill_ != nullptr)
	{
		skill_->Init();
	}
	if (second_skill_ != nullptr)
	{
		second_skill_->Init();
	}
	avoid_->Init();
	test_behavior_->Init();
	
	EffectManager::GetInstance().Play(EffectID::kHandAura);
	EffectManager::GetInstance().Play(EffectID::kHandAura2);
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_I)) { status_container_->TakeHeal(10); }
	if (status_container_->GetCurrentStatus().hp <= 0)
	{
		animator_->PlayRequest("death");
	}
	else
	{
		
		Move();
		if (skill_ != nullptr)
		{
			skill_->Update();
		}

		if (second_skill_ != nullptr)
		{
			second_skill_->Update();
		}
		avoid_->Update();
		rigid_body_->SetTargetVelocity(vel_);
		test_behavior_->Update();
	}
	
	animator_->Update();
	Setting();
	// 参照の更新
	UpdateBone();
	// エフェクトを発生
	EffectUpdate();
	on_damage_ = FALSE;
}

void Player::LateUpdate()
{
	head_pos_ = VAdd(pos_, VGet(0.f, 10.f, 0.f));
}

void Player::ResetVelocity()
{
	rigid_body_->ResetVelocity();
}

void Player::SetTragetVelocity(const VECTOR& velocity)
{
	vel_ = velocity;
}

void Player::SetVelocity(const VECTOR& velocity)
{
	vel_ = velocity;
}

void Player::SetRotation(const VECTOR& rot)
{
	rot_ = rot;
	target_rot_y_ = rot_.y;
}

void Player::SetDirection(const VECTOR& direction)
{
	dir_ = direction;
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
	
	if (FALSE) { return; }
	if (skill_ != nullptr) { skill_->Debug(); }
	if (second_skill_ != nullptr) { second_skill_->Debug(); }
	
	status_container_->Debug();
	if (TRUE) { return; }
	//my_area_->Debug();
	rigid_body_->Debug();
	
	
	//skill_->Debug();
	//test_behavior_->Debug();
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

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "rot", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(rot_);

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "vel", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(vel_);

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "camera_dir", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(*camera_dir_);
	
	if (is_ground_)
	{
		DrawString(0, Debug::GetInstance().GetNowLineSize(), "着地", Color::kWhite);
	}
	else
	{
		DrawString(0, Debug::GetInstance().GetNowLineSize(), "着地じゃない", Color::kWhite);
	}
	Debug::GetInstance().Add();
	if (is_invincible_)
	{
		DrawString(0, Debug::GetInstance().GetNowLineSize(), "無敵", Color::kWhite);
	}
	else
	{
		DrawString(0, Debug::GetInstance().GetNowLineSize(), "無敵じゃない", Color::kWhite);
	}
	Debug::GetInstance().Add();
	if (is_stop_)
	{
		DrawString(0, Debug::GetInstance().GetNowLineSize(), "stop", Color::kWhite);
	}
	else
	{
		DrawString(0, Debug::GetInstance().GetNowLineSize(), "not_stop", Color::kWhite);
	}

	Debug::GetInstance().Add();
}

void Player::LoadFile(const char* file_path,const std::string my_name)
{
	std::ifstream file("data/csv/players/players_data.csv");
	std::string line;
	float avoid_speed = 0.f;
	std::string job = "";
	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の2行を飛ばす
	std::getline(file, line);
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::getline(ss, data, ',');
		if (data != my_name) { continue; }

		// モデルのパス
		std::string path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		handle_ = MV1LoadModel(path.c_str());
		if(handle_ == -1){ printfDx("player : モデル読み込みエラー\n"); }
		VECTOR init_pos = VectorAssistant::VGetZero();
		
		// 初期pos
		pos_ = CSVFileAssistant::GetVectorOfCSVFile(ss, data);
		VECTOR rot = CSVFileAssistant::GetVectorOfCSVFile(ss, data);
		
		if (TRUE)
		{
			rot_.x = RadianAssistant::kOneRad * rot.x;
			rot_.y = RadianAssistant::kOneRad * rot.y;
			rot_.z = RadianAssistant::kOneRad * rot.z;
		}
		
		// skill
		skill1_id_ = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		skill2_id_ = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		
		speed_		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		avoid_speed = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		job = CSVFileAssistant::GetStringOfCSVFile(ss, data);

		break;
	}
	file.close();
	/*スキルを作っていくよ*/
	//avoidskill

	avoid_ = std::make_shared<AvoidSkill>(std::dynamic_pointer_cast<Player>(shared_from_this()),avoid_speed);

}

void Player::MakeSkill(std::weak_ptr<Player> owner)
{

	auto skill = SkillLoader::GetInstance().SkillLoad(skill1_id_, name_, owner);
	auto second_skill = SkillLoader::GetInstance().SkillLoad(skill2_id_, name_, owner);
	skill_ = skill;
	second_skill_ = second_skill;
	if (skill_ == nullptr)
	{
		printfDx("失敗\n");
	}

	if (second_skill_ == nullptr)
	{
		printfDx("失敗\n");
	}

}

void Player::Move()
{
	if (animator_->GetNowAnimName() == "idle") 
	{
		if (!on_damage_) { can_move_ = TRUE; }
	}
	VECTOR dir = VectorAssistant::VGetZero();
	vel_ = VectorAssistant::VGetZero();
	float speed = speed_;

	if (animator_->GetNowAnimName() != "punch")
	{
		dir.x = input_->GetMoveDir().x;
		dir.z = input_->GetMoveDir().y;
	}
	
	if (VSize(dir) > 0 && !is_stop_ && can_move_)
	{
		auto input = std::dynamic_pointer_cast<const PlayerInput>(input_);
		if (input != nullptr) 
		{
			dir_ = VectorAssistant::VGetRotPiY(VectorAssistant::VGetFlat(*camera_dir_), VectorAssistant::VGetTan(dir));
		}
		dir_ = VNorm(dir_);
		
		if (input_->IsDash())
		{
			speed *= 2.5f;
			is_dash_ = TRUE;
			animator_->PlayRequest("run");
		}
		else
		{
			is_dash_ = FALSE;
			animator_->PlayRequest("jogging");
		}
		is_move_ = TRUE;
		vel_ = VScale(dir_, speed);
	}
	else
	{
		is_move_ = FALSE;
		is_dash_ = FALSE;

		animator_->PlayRequest("idle");

	}
	
	
	vel_ = VScale(vel_, FPS::GetInstance().GetDeltaTime() * 60.f);
	vel_ = VAdd(vel_, VGet(0.f, -fall_speed_, 0.f));
	
	if (VSize(dir) > 0.f)
	{ 
		dir_ = VNorm(vel_);
		target_rot_y_ = VectorAssistant::VGetTan(VectorAssistant::VGetReverce(dir_));
	}
	if (is_stop_) { return; }
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
	int right_hand_bone_num				= 0;
	int left_hand_bone_num				= 0;
	const TCHAR* right_hand_bone_path	= "mixamorig:RightHand";
	const TCHAR* left_hand_bone_path	= "mixamorig:LeftHand";
	//boneのidを取得
	right_hand_bone_num		= MV1SearchFrame(handle_, right_hand_bone_path);
	left_hand_bone_num		= MV1SearchFrame(handle_, left_hand_bone_path);
	//matrixを取得
	const MATRIX right_hand_mat	= MV1GetFrameLocalWorldMatrix(handle_, right_hand_bone_num);
	const MATRIX left_hand_mat	= MV1GetFrameLocalWorldMatrix(handle_, left_hand_bone_num);
	//posを取得
	const VECTOR right_hand_pos	= VectorAssistant::VGetPositionFromMatrix(right_hand_mat);
	const VECTOR left_hand_pos	= VectorAssistant::VGetPositionFromMatrix(left_hand_mat);
	right_hand_pos_				= right_hand_pos;
	left_hand_pos_				= left_hand_pos;
}

void Player::DecideAttackTarget()
{
	// 攻撃対象が範囲内にいないならやめる
	attack_target_pos_ = VectorAssistant::VGetZero();
	is_attack_target_in_range_ = FALSE;
	if (my_area_->GetMyAreaObject().size() == 0) { return; }
	
	// enemyの中から近い敵を攻撃対象に動く
	int enemy_num = 0;
	std::map<float, VECTOR> dist_pos_mp;

	for (const auto my_area_objects : my_area_->GetMyAreaObject())
	{
		const auto enemy = std::dynamic_pointer_cast<EnemyBase>(my_area_objects.lock());
		if (enemy != nullptr)
		{
			enemy_num++;
			is_attack_target_in_range_	= TRUE;
			const VECTOR	enemy_pos	= enemy->GetPosition();
			const float		dist_size	= VSize(VSub(enemy_pos, pos_));
			dist_pos_mp[dist_size]		= enemy_pos;
		}
	}
	if (enemy_num == 0) { return; }
	
	if (dist_pos_mp.size() > 0)
	{
		auto most_near_pos = dist_pos_mp.begin()->second;
		attack_target_pos_ = most_near_pos;
	}
}

void Player::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	//何かが当たった時の処理
	std::string target_tag = object->GetRigidBody()->GetTag();

	if (target_tag == "stage")
	{

	}

	if (target_tag == "enemy")
	{
		// printfDx("enemy");
		return;
	}

	if (target_tag == "punch")
	{
		// 自身とオーナーが一緒かを確認
		if (is_invincible_) { return; }
		if (auto punch = std::dynamic_pointer_cast<Punch>(object))
		{
			if (!punch->CheckSameOwner(std::dynamic_pointer_cast<ObjectBase>(shared_from_this())))
			{
				animator_->PlayRequest("on_damage");
				can_move_ = FALSE;
			}
		}
		return;
	}

	if (target_tag == "double_punch")
	{
		// rigidbodyのオーナと自身が一緒の場合は除外
		if (is_invincible_) { return; }
		if (!object->GetRigidBody()->CheckSameOwner(shared_from_this()))
		{
			animator_->PlayRequest("on_damage");
			can_move_ = FALSE;
		}
		return;
	}

	if (target_tag == "tackle")
	{
		if (is_invincible_) { return; }
		animator_->PlayRequest("knock_back");
		can_move_ = FALSE;
		return;
	}

	if (target_tag == "stamp")
	{
		if (is_invincible_) { return; }
		animator_->PlayRequest("on_damage");
		can_move_ = FALSE;
		return;
	}

	if (target_tag == "effect_attack")
	{
		if (is_invincible_) { return; }
		// 自身とオーナーのパンチがplayerにcastしてnullptrなったら処理する
		if (!object->GetRigidBody()->CheckSameOwner(shared_from_this()))
		{
			animator_->PlayRequest("knock_back");
			can_move_ = FALSE;
		}
		return;
	}

}

void Player::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void Player::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void Player::OnGround(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto check_area = std::dynamic_pointer_cast<CheckMyArea>(object);

	if (check_area != nullptr) { return; }
}

void Player::UnGround()
{
	is_ground_ = FALSE;
	// printfDx("1\n");
}

void Player::OnHealFromPlayer(float heal)
{
	// printfDx("ヒール\n");
}

void Player::OnDamageFromEnemy(float damage,AttackType type)
{
	// 無敵時はダメージを受けない
	if (is_invincible_) 
	{
		// この瞬間にエフェクトを描画
		//printfDx("無敵\n");
		EffectManager::GetInstance().Play(EffectID::kAvoidSuccess);
		EffectManager::GetInstance().SetPos(EffectID::kAvoidSuccess,pos_);
		EffectManager::GetInstance().End(EffectID::kAvoidSuccess, EffectEndState::kTotal);
		return;
	}
	on_damage_ = TRUE;
	status_container_->TakeDamage(damage,type);
	//printfDx("ダメージを受けちゃってます\n");
}

void Player::InputChange(std::shared_ptr<InputBase> input)
{
	input_ = input;
}

std::vector<std::weak_ptr<ObjectBase>> Player::GetMyAreaObject()
{
	return my_area_->GetMyAreaObject();
}

std::shared_ptr<RigidBody> Player::GetRigidBody()
{
	return rigid_body_;
}

VECTOR* Player::GetHeadPos()
{
	return &head_pos_;
}

VECTOR* Player::GetRightHandPos()
{
	return &right_hand_pos_;
}

VECTOR* Player::GetLeftHandPos()
{
	return &left_hand_pos_;
}

VECTOR* Player::GetPosPtr()
{
	return &pos_;
}

std::shared_ptr<StatusContainer> Player::GetStatusContainer()
{
	return status_container_;
}

const std::shared_ptr<const InputBase> Player::GetInput() const
{
	return input_;
}

const float Player::GetDetectionRadius() const
{
	return detection_radius_;
}

const bool Player::GetIsMove() const
{
	return is_move_;
}

const bool Player::GetOnGround() const
{
	return rigid_body_->GetOnGround();
}

const bool Player::GetIsDash() const
{
	return is_dash_;
}

const bool Player::GetIsStop() const
{
	return is_stop_;
}

const bool Player::GetCanMove() const
{
	return can_move_;
}

const VECTOR Player::GetDirection() const
{
	return dir_;
}

const VECTOR Player::GetInputDir() const
{
	VECTOR input_dir = input_->GetMoveDir();	// inputから移動方向を受け取る

	// 入力がない場合はそのまま向いている方向に行く
	if (VSize(input_dir) == 0.f) { return dir_; }

	const auto ai_input = std::dynamic_pointer_cast<const AIInput>(input_);
	if (ai_input != nullptr)
	{
		return input_dir;	// ai_inputにする
	}
	// カメラの方向に補正させる
	input_dir = VGet(input_dir.x, 0.f, input_dir.y);
	input_dir = VectorAssistant::VGetRotPiY(VectorAssistant::VGetFlat(*camera_dir_), VectorAssistant::VGetTan(input_dir));
	input_dir = VNorm(input_dir);
	return input_dir;
}

void Player::EffectUpdate()
{
	VECTOR effect_right_hand_pos = VGet(right_hand_pos_.x, right_hand_pos_.y - 1.f, right_hand_pos_.z);
	VECTOR effect_left_hand_pos = VGet(left_hand_pos_.x, left_hand_pos_.y - 1.f, left_hand_pos_.z);

	EffectManager::GetInstance().SetPos(EffectID::kHandAura,effect_right_hand_pos);
	EffectManager::GetInstance().SetPos(EffectID::kHandAura2,effect_left_hand_pos);
}