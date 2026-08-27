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
#include"jump_skill.h"
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
#include"attack_type.h"
#include"effect_manager.h"
#include"effect_id.h"
#include"effect_end_state.h"
#include"time.h"
#include"damage_ui_group.h"
#include"player_ui_group_interface.h"
#include"sound_manager.h"
#include"condition_timer.h"
#include"brain.h"
#include"player_observer_interface.h"
#include"shadow_creater_interface.h"

Player::Player(VECTOR* camera_dir,std::shared_ptr<const InputBase> input,const std::string name, std::shared_ptr<IPlayerUIGroup> player_ui_group,std::shared_ptr<IShadowCreater> shadow_creater)
	: CharacterBase("player")
	, IPhysicsEventReceiver()
	, name_(name)
	, input_(input)
	, player_ui_group_(player_ui_group)
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
	float radius = 1.5f;
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(radius, 6.f, VectorAssistant::VGetZero()), 
		&pos_, TRUE, FALSE, 0.03f, 0.1f);
	enemy_death_offset_timer_ = std::make_shared<ConditionTimer>(2.8f);
	VECTOR hp_pos = VectorAssistant::VGet2D(300.f, 800.f);
	VECTOR hp_size = VectorAssistant::VGet2D(100.f, 30.f);
	status_container_ = std::make_shared<StatusContainer>(name_,hp_pos, hp_size);
	fall_speed_ = 0.f;
	avoid_stamina_consumption_ = -1.f;
	is_move_ = FALSE;
	is_dash_ = FALSE;
	is_attack_target_in_range_ = FALSE;
	is_stop_ = FALSE;
	can_move_ = TRUE;
	on_damage_ = FALSE;
	is_death_enemy_ = FALSE;
	//input_ = input;
	target_rot_y_ = 0;
	speed_ = 0.f;
	job_ = "nothing";
	shadow_creater->CreateShadow(&pos_, radius +0.5f);
}

Player::~Player()
{
	
}

void Player::AddObserver(IPlayerObserver* observer)
{
	observers_.push_back(observer);
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
	
	// もともとのhp
	std::function<int()> get_base_hp = [this]() -> int
		{
			return static_cast<int>(status_container_->GetBaseStatus().hp);
		};
	// 現在のhp
	std::function<int()> get_current_hp = [this]() -> int
		{
			return static_cast<int>(status_container_->GetCurrentStatus().hp);
		};
	// もともとのstamina
	std::function<float()> get_base_stamina = [this]() -> float
		{
			return status_container_->GetBaseStatus().stamina;
		};
	// 現在のstamina
	std::function<float()> get_current_stamina = [this]() -> float
		{
			return status_container_->GetCurrentStatus().stamina;
		};
	// スタミナが使えるか
	std::function<bool()> can_use_stamina = [this]() -> bool
		{
			return status_container_->CanUseStamina();
		};

	// 回避に使うスタミナ量
	std::function<float()> get_avoid_stamina = [this]() {return avoid_stamina_consumption_; };

	// ui表示
	player_ui_group_->MakeUI(get_base_hp, get_current_hp, name_);

	// スタミナのui表示
	player_ui_group_->MakeStaminaUI(get_base_stamina, get_current_stamina, can_use_stamina, get_avoid_stamina);

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
	
	time_->Init();
	//rigid_body_->SetUpSpeed(10);
	//EffectManager::GetInstance().Play(EffectID::kHandAura);
	//EffectManager::GetInstance().Play(EffectID::kHandAura2);
}

void Player::Update()
{
	time_->Update();
	if (CheckHitKey(KEY_INPUT_I)) { status_container_->TakeHeal(10); }

	if (input_->IsLockOnEnemy()) 
	{
		Brain::GetInstance().ChangeCamera("lock_on_enemy");
	}
	else
	{
		if (Brain::GetInstance().GetCurrentCameraName() == "lock_on_enemy")
		{
			Brain::GetInstance().ChangeCamera("sphere");
		}
	}
	

	if (is_death_enemy_)
	{
		enemy_death_offset_timer_->Update();
		if (enemy_death_offset_timer_->GetIsEnd())
		{
			can_move_ = FALSE;
			animator_->PlayRequest("won");
		}
	}

	if (status_container_->GetCurrentStatus().hp <= 0)
	{
		animator_->PlayRequest("death");
		rigid_body_->SetTargetVelocity(VectorAssistant::VGetZero());
		//rigid_body_->SetVelocity(VectorAssistant::VGetZero());
		rigid_body_->NotActive();
	}
	else
	{
		status_container_->Update();
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
		jump_->Update();
	}
	if (rigid_body_->GetOnGround())
	{
		animator_->PlayRequest("idle");
	}
	else
	{
		animator_->PlayRequest("falling");
	}
	animator_->Update(time_);
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
	if (FALSE) { return; }
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
		avoid_stamina_consumption_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		job = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		job_ = job;
		break;
	}
	file.close();
	/*スキルを作っていくよ*/
	auto mine = std::dynamic_pointer_cast<Player>(shared_from_this());
	avoid_ = std::make_shared<AvoidSkill>(mine,avoid_speed,avoid_stamina_consumption_);
	std::pair<float, float> timing;
	timing.first = 0.17f;
	timing.second = 1.f;
	jump_ = std::make_shared<JumpSkill>(mine, timing,1.f);
}

void Player::MakeSkill(std::weak_ptr<Player> owner)
{
	auto skill = SkillLoader::SkillLoad(skill1_id_, name_, owner,SkillType::kNormal);
	auto second_skill = SkillLoader::SkillLoad(skill2_id_, name_, owner,SkillType::kStrong);

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
		if (!on_damage_ && !is_death_enemy_) { can_move_ = TRUE; }
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
		
		if (input_->IsDash() && status_container_->CanUseStamina())
		{
			speed *= 2.5f;
			is_dash_ = TRUE;
			if(rigid_body_->GetOnGround())
			{
				animator_->PlayRequest("run");
			}
			

			// ここでスタミナを減らす
			status_container_->StaminaDown(0.5f * time_->GetDeltaTime());
		}
		else
		{
			is_dash_ = FALSE;
			if (rigid_body_->GetOnGround())
			{
				animator_->PlayRequest("jogging");
			}
		}
		is_move_ = TRUE;
		vel_ = VScale(dir_, speed);
	}
	else
	{
		is_move_ = FALSE;
		is_dash_ = FALSE;
	}
	
	
	vel_ = VScale(vel_, time_->GetFPSRate());
	vel_ = VAdd(vel_, VGet(0.f, -fall_speed_, 0.f));
	
	if (VSize(dir) > 0.f)
	{ 
		dir_ = VNorm(vel_);
		target_rot_y_ = VectorAssistant::VGetTan(VectorAssistant::VGetReverce(dir_));
	}
	if (is_stop_) { return; }
	rot_.y = RadianAssistant::Lerp(rot_.y, target_rot_y_, RadianAssistant::kOneRad * 15.f * time_->GetFPSRate());
	// if (CheckHitKey(KEY_INPUT_SPACE)) { pos_ = VGet(0.f, 0.f, 0.f); vel_ = VGet(0.f, 0.f, 0.f); is_ground_ = FALSE; fall_speed_ = 0.f;}
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
		float size = VSize(VSub(pos_, object->GetRigidBody()->GetPosition()));
		float my_radius = std::dynamic_pointer_cast<Capsule>(rigid_body_->GetCollider())->GetRadius();
		float other_radius = std::dynamic_pointer_cast<Sphere>(object->GetRigidBody()->GetCollider())->GetRadius();
		printfDx("my_radius:%.2f,other_radius:%.2f,%.2f\n", my_radius,other_radius,size);
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
		// padの振動

		// 許容量
		const float kJustAvoidRatio = 0.37f;
		// ダメージを受けない
		// 無敵かつジャスト入力中かつアニメーションが最初のほうなら特別処理
		if (animator_->GetRatio("avoid") < kJustAvoidRatio)
		{
			// バフをかける
			status_container_->StaminaUpMax();

			if (job_ == "healer")
			{
				// hpの回復
				status_container_->TakeHeal(status_container_->GetCurrentStatus().magic_atk);
			}
			else
			{
				// バフ
				status_container_->Activation(job_ + "_avoid",player_ui_group_);
			}

			int effect_id = -1;

			if (job_ == "attacker")
			{ 
				effect_id = EffectID::kAttackerJastAvoid;
			}
			else if (job_ != "healer")
			{
				effect_id = EffectID::kHealerJastAvoid;
			}
			else if (job_ == "")
			{
				effect_id = EffectID::kDefenderJastAvoid;
			}

			EffectManager::GetInstance().Play(effect_id);
			EffectManager::GetInstance().SetPos(effect_id, pos_);
			EffectManager::GetInstance().End(effect_id, EffectEndState::kTotal);
			
			
			// この時ジャスト回避
			//printfDx("ジャスト回避\n");
			time_->SetTimeScale(0.f, 0.15f);
			rigid_body_->SetStop(0.15f);
			SoundManager::GetInstance().SetPos("just_avoid", pos_);
			SoundManager::GetInstance().Play3DSound("just_avoid");

			for (auto& observer : observers_)
			{
				observer->OnPlayerJustAvoid();
			}

		}
		SoundManager::GetInstance().SetPos("avoid_collect", pos_);
		SoundManager::GetInstance().Play3DSound("avoid_collect");
		// この瞬間にエフェクトを描画
		EffectManager::GetInstance().Play(EffectID::kAvoidSuccess);
		EffectManager::GetInstance().SetPos(EffectID::kAvoidSuccess,pos_);
		EffectManager::GetInstance().End(EffectID::kAvoidSuccess, EffectEndState::kTotal);
		
		for (auto& observer : observers_)
		{
			observer->OnPlayerAvoidCollect();
		}

		return;
	}
	on_damage_ = TRUE;
	// ダメージ量をもらう
	auto final_damage = status_container_->TakeDamage(damage,type);

	if (status_container_->GetCurrentStatus().hp <= 0)
	{
		Brain::GetInstance().ChangeCamera("lose");

		for (auto& observer : observers_)
		{
			observer->OnPlayerDeath();
		}
	}
	// サウンドを再生
	SoundManager::GetInstance().Play3DSound("palyer_on_damage");
	// ui描画を行う
	// 頭のpositionにしようかな
	DamageUIGroup::GetInstance().SpawnPlayerDamageUI(head_pos_, final_damage);
}

void Player::InputChange(std::shared_ptr<InputBase> input)
{
	input_ = input;
}

void Player::OnEnemyDeath()
{
	// 勝利アニメーションの再生
	is_death_enemy_ = TRUE;
}

std::vector<std::weak_ptr<ObjectBase>> Player::GetMyAreaObject()
{
	return my_area_->GetMyAreaObject();
}

std::shared_ptr<RigidBody> Player::GetRigidBody()
{
	return rigid_body_;
}

const float Player::GetDeltaTime() const
{
	return time_->GetFPSRate();
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

const int Player::GetSkillID(SkillType type) const
{
	switch (type)
	{
	case SkillType::kNormal:
		return skill_->GetID();
		break;
	case SkillType::kStrong:
		return second_skill_->GetID();
		break;
	case SkillType::kConstant:
	default:
		return -1;
		break;
	}
	return FALSE;
}

const float Player::GetSkillCoolTime(SkillType type) const
{
	switch (type)
	{
	case SkillType::kNormal:
		return skill_->GetCoolTiemRatio();
		break;
	case SkillType::kStrong:
		return second_skill_->GetCoolTiemRatio();
		break;
	case SkillType::kConstant:
	default:
		return -1.f;
		break;
	}
	return -1.f;
}

const bool Player::GetSkillCanUse(SkillType type) const
{
	switch (type)
	{
	case SkillType::kNormal:
		return skill_->CanUseSkill();
		break;
	case SkillType::kStrong:
		return second_skill_->CanUseSkill();
		break;
	case SkillType::kConstant:
	default:
		return FALSE;
		break;
	}
	return FALSE;
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

	//EffectManager::GetInstance().SetPos(EffectID::kHandAura,effect_right_hand_pos);
	//EffectManager::GetInstance().SetPos(EffectID::kHandAura2,effect_left_hand_pos);
}