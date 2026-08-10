#include<iostream>
#include<memory>
#include<string>
#include<functional>
#include<utility>
#include"DxLib.h"
#include"enemy_base.h"
#include"sphere.h"
#include"capsule.h"
#include"rigid_body.h"
#include"FPS.h"
#include"vector_assistant.h"
#include"debug.h"
#include"physics.h"
#include"object_setter.h"
#include"animator_base.h"
#include"animator_enemy.h"
#include"punch.h"
#include"check_my_area.h"
#include"behavior_tree.h"
#include"behavior_status.h"
#include"behavior_base.h"
#include"character_behavior.h"
#include"double_punch.h"
#include"jumping_attack.h"
#include"area_of_effect_attack.h"
#include"jump.h"
#include"stamp.h"
#include"tackle.h"
#include"animation_charge.h"
#include"chase_player.h"
#include"color.h"
#include"node_base.h"
#include"composite_node.h"
#include"sequence_node.h"
#include"random_node.h"
#include"branch_node.h"
#include"action_node.h"
#include"player_group.h"
#include"effect_id.h"
#include"attack_type.h"
#include"status.h"
#include"status_container.h"
#include"disp_attack_range.h"
#include"enemy_ui_group.h"
#include"time.h"
#include"change_method.h"
#include"hit_red_body.h"
#include"damage_ui_group.h"
#include"play_sound.h"

EnemyBase::EnemyBase(const VECTOR& pos)
	: CharacterBase("enemy")
	, IPhysicsEventReceiver()
{
	vel_ = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	target_player_pos_ = VectorAssistant::VGetZero();
	pos_ = pos;
	double_punch_coll_pos_ = VectorAssistant::VGetZero();
	right_hand_pos_ = VectorAssistant::VGetZero();
	scale_ = VectorAssistant::VGetSame(0.15f);
	my_name_ = "";
	handle_ = MV1LoadModel("data/model/enemy/zako/Demon_T_Wiezzorek.mv1");
	if (handle_ == -1) { printfDx("読み込みエラー\n"); }
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(6.5f, 18.f, VectorAssistant::VGetZero()), 
		&pos_, TRUE, FALSE, 0.03f,0.1f);
	fall_speed_ = 0.f;

	VECTOR hp_pos = VectorAssistant::VGet2D(1000.f, 100.f);
	VECTOR hp_size = VectorAssistant::VGet2D(500.f, 50.f);

	status_container_ = std::make_shared<StatusContainer>("zako",hp_pos,hp_size);
	hit_red_body_ =	 std::make_shared<HitRedBody>(handle_);
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Init()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("enemy");
	// physicsの登録
	Physics::GetInstance().AddBody(rigid_body_);
	// setterへの登録
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
	auto physics_mine = shared_from_this();
	auto mine = std::dynamic_pointer_cast<EnemyBase>(physics_mine);
	std::shared_ptr<ObjectBase> obj_mine = mine;

	std::pair<float, float> timing;
	timing.first = 0.38f;
	timing.second = 0.45f;
	// 両手パンチのノードを生成
	std::shared_ptr<BehaviorBase> double_punch = std::make_shared<DoublePunch>(std::dynamic_pointer_cast<ObjectBase>(mine),
		"double_punch", 0.35f, 0.5f, &double_punch_coll_pos_, 3.0f, 6.f,1.f);
	std::shared_ptr<NodeBase> double_punch_node = std::make_shared<ActionNode>(double_punch);

	// 上から降ってくるノードを生成
	std::vector<std::shared_ptr<NodeBase>> stump_nodes;

	auto ui_stump_end_function = [this]() -> bool {return rigid_body_->GetIsLanding(); };
	float stump_radius = 60.f;
	stump_nodes.push_back(std::make_shared<ActionNode>
		(std::make_shared<DispAttackRange>(obj_mine, &pos_, VGet(stump_radius, 1.f, stump_radius), ui_stump_end_function)));

	stump_nodes.push_back(std::make_shared<ActionNode>(std::make_shared<Jump>(mine,
		"jumping_attack", timing, 1.f)));

	stump_nodes.push_back(std::make_shared<ActionNode>
		(std::make_shared<Stamp>(obj_mine, &pos_, stump_radius,"jumping_attack",2.f)));

	std::shared_ptr<NodeBase> stamp_node = std::make_shared<SequenceNode>(stump_nodes);
	
	// エフェクトによる攻撃
	std::vector<std::shared_ptr<NodeBase>>  area_of_effect_nodes;
	float area_of_effect_radius = 10.f;

	// 攻撃
	std::shared_ptr<NodeBase> area_of_effect_node = std::make_shared<ActionNode>(std::make_shared<AreaOfEffectAttack>(
		obj_mine, "charge", 0.f, 0.9f, VectorAssistant::VGetSame(2.f), area_of_effect_radius, EffectID::kAreaOfEffect, 2.f,1.f));
	
	// ノード終わりじゃなく当たり判定が終わったら描画させたいよね
	// 終了条件はこのbehaviorが終了しているとき
	auto ui_AoE_end_function = [area_of_effect_node]() -> bool { return area_of_effect_node->GetStatus() == BehaviorStatus::kComplete; };

	// ui表示
	std::shared_ptr<NodeBase> area_of_effect_ui_node = std::make_shared<ActionNode>(std::make_shared<DispAttackRange>(
		obj_mine, &target_player_pos_, VGet(area_of_effect_radius, 1.f, area_of_effect_radius), ui_AoE_end_function));


	// ui表示から先に入れる
	area_of_effect_nodes.push_back(area_of_effect_ui_node);
	area_of_effect_nodes.push_back(area_of_effect_node);

	std::shared_ptr<NodeBase> tackle_voice_node = std::make_shared<ActionNode>(
		std::make_shared<PlaySound3D>(mine, &pos_, "tackle_voice"));

	// タックルの前の予備動作
	std::shared_ptr<NodeBase> charge_tackle_node = 
		std::make_shared<ActionNode>(std::make_shared<AnimationCharge>(mine, "charge_tackle", 0.9f));

	// タックル
	std::shared_ptr<NodeBase> tackle_node = std::make_shared<ActionNode>(
		std::make_shared<Tackle>(mine,
			std::make_shared<RigidBody>(std::make_shared<Capsule>(10.5f, 18.f, VectorAssistant::VGetZero()), &pos_, FALSE, TRUE, 0.1f, 1.f), "tackle", 1.f, 2.f,1.f));
	
	std::vector<std::shared_ptr<NodeBase>> tackle_nodes;
	
	tackle_nodes.emplace_back(tackle_voice_node);
	tackle_nodes.emplace_back(charge_tackle_node);
	tackle_nodes.emplace_back(tackle_node);

	// ランダムのnodeに代入
	std::vector<std::shared_ptr<NodeBase>> random_nodes;
	random_nodes.emplace_back(stamp_node);
	//random_nodes.emplace_back(double_punch_node);
	//random_nodes.emplace_back(std::make_shared<SequenceNode>(area_of_effect_nodes));
	//random_nodes.emplace_back(std::make_shared<SequenceNode>(tackle_nodes));

	// 追いかけるときのノード
	std::vector<std::shared_ptr<NodeBase>> random_nodes2;

	//random_nodes2.emplace_back(area_of_effect_node);
	/*
	
	*/
	std::shared_ptr<NodeBase> radom_attack_node = std::make_shared<RandomNode>(random_nodes);

	target_player_pos_ = PlayerGroup::GetInstance().MostNearPlayerPos(pos_);
	std::shared_ptr<NodeBase> chase_node = std::make_shared<ActionNode>(std::make_shared<ChasePlayer>(obj_mine,
		"run", &target_player_pos_, 0.5f));
	/*------*/

		// エフェクトによる攻撃
	std::vector<std::shared_ptr<NodeBase>>  area_of_effect_nodes2;
	float area_of_effect_radius2 = 10.f;

	// 攻撃
	std::shared_ptr<NodeBase> area_of_effect_node2 = std::make_shared<ActionNode>(std::make_shared<AreaOfEffectAttack>(
		obj_mine, "charge", 0.f, 0.9f, VectorAssistant::VGetSame(2.f), area_of_effect_radius2, EffectID::kAreaOfEffect, 2.f,1.f));

	// ノード終わりじゃなく当たり判定が終わったら描画させたいよね
	// 終了条件はこのbehaviorが終了しているとき
	auto ui_AoE_end_function2 = [area_of_effect_node2]() -> bool { return area_of_effect_node2->GetStatus() == BehaviorStatus::kComplete; };

	// ui表示
	std::shared_ptr<NodeBase> area_of_effect_ui_node2 = std::make_shared<ActionNode>(std::make_shared<DispAttackRange>(
		obj_mine, &target_player_pos_, VGet(area_of_effect_radius2, 1.f, area_of_effect_radius2), ui_AoE_end_function2));


	// ui表示から先に入れる
	area_of_effect_nodes2.push_back(area_of_effect_ui_node2);
	area_of_effect_nodes2.push_back(area_of_effect_node2);
	/*-------*/
	random_nodes2.emplace_back(std::make_shared<SequenceNode>(area_of_effect_nodes2));
	random_nodes2.emplace_back(chase_node);

	std::shared_ptr<NodeBase> random_far_nodes2 = std::make_shared<RandomNode>(random_nodes2);

	std::pair<std::shared_ptr<NodeBase>, std::shared_ptr<NodeBase>> nodes_;
	//nodes_.first = random_far_nodes2;
	nodes_.first = random_far_nodes2;
	nodes_.second = radom_attack_node;
	
	std::function<bool()> condition = [this]()-> bool
	{
		float dist_to_player = VSize(VSub(target_player_pos_, pos_));
		return dist_to_player > 10.f;
	};
	
	std::shared_ptr<NodeBase> first_node = std::make_shared<BranchNode>(nodes_,
		condition);
	
	/*
	* std::shared_ptr<NodeBase> first_node = chase_node;
	*/
	
	behavior_tree_ = std::make_shared<BehaviorTree>(first_node);

	std::function<int()> get_base_hp = [this]()-> int
		{
			return static_cast<int>(status_container_->GetBaseStatus().hp);
		};

	std::function<int()> get_current_hp = [this]()-> int
		{
			return static_cast<int>(status_container_->GetCurrentStatus().hp);
		};
	time_->Init();

	// uiを作成
	EnemyUIGroup::GetInstance().MakeStatusUI(get_base_hp, get_current_hp, "zako");


	UpdateBone();
	/*
	test_behavior_ = std::make_shared<DoublePunch>(std::dynamic_pointer_cast<ObjectBase>(mine),
		"double_punch", 0.35f, 0.5f, &double_punch_coll_pos_, 3.0f, 6.f);
	*/
	/*
	test_behavior_ = std::make_shared<JumpingAttack>
		(obj_mine, &pos_, 0.5f, 0.75f, "jumping_attack");
	*/
	/*
	test_behavior_ = std::make_shared<Jump>
		(obj_mine, "jumping_attack" , 0.38f, 1.f);
	*/
	
	
	animator_ = std::make_shared<AnimatorEnemy>(handle_,"enemy");
	animator_->Init();
	status_container_->Init();
	hit_red_body_->Init();
	// test_behavior_->Init();
	behavior_tree_->Init();
	dir_ = VectorAssistant::VGetDirFromRotY(rot_);
}

void EnemyBase::Update()
{
	time_->Update();
	if (status_container_->GetCurrentStatus().hp <= 0)
	{
		animator_->PlayRequest("death");
		// printfDx("%s\n",animator_->GetNowAnimName().c_str());
	}
	else
	{
		// 一番近いプレイヤーの位置を取得
		target_player_pos_ = PlayerGroup::GetInstance().MostNearPlayerPos(pos_);
		VECTOR dir = VectorAssistant::VGetZero();
		//dir_ = VectorAssistant::VGetZero();
		// vel_ = dir;

		double_punch_coll_pos_ = VAdd(pos_, VScale(dir_, 5.f));

		rigid_body_->SetTargetVelocity(vel_);
		behavior_tree_->Update();
		//test_behavior_->Update();
	}
	
	animator_->Update(time_);
	UpdateBone();
	hit_red_body_->Update();
	
}

void EnemyBase::LateUpdate()
{

}

void EnemyBase::Draw()
{
	//MV1SetDifColorScale(handle_, GetColorF(100.0f, 0.0f, 0.0f, 1.0f));
	//MV1SetSpcColorScale(handle_, GetColorF(100.0f, 0.0f, 0.0f, 1.0f));
	//MV1SetEmiColorScale(handle_, GetColorF(100.0f, 0.0f, 0.0f, 1.0f));
	//MV1SetAmbColorScale(handle_, GetColorF(1.f, 1.f, 1.f, 1.f));
	hit_red_body_->DoRedColor();
	
	MV1DrawModel(handle_);
}

void EnemyBase::Debug()
{
	if (FALSE) { return; }

	status_container_->Debug();

	behavior_tree_->Debug();
	rigid_body_->Debug();
	if (TRUE) { return; }
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "----------enemy-----------", Color::kWhite);
	Debug::GetInstance().Add();
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "pos", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(pos_);
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "target_player_pos", Color::kWhite);
	Debug::GetInstance().Add();
	Debug::GetInstance().DrawVector(target_player_pos_);
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "%s", animator_->GetNowAnimName().c_str());
	Debug::GetInstance().Add();

	// test_behavior_->Debug();
}

void EnemyBase::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto target_tag = object->GetRigidBody()->GetTag();
	if (target_tag == "punch")
	{
		if (!object->GetRigidBody()->CheckSameOwner(shared_from_this()))
		{
			// animator_->PlayRequest("on_damage");
		}
	}
}

void EnemyBase::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void EnemyBase::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void EnemyBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	auto target_tag = object->GetRigidBody()->GetTag();
	if (target_tag == "punch")
	{
		if (!object->GetRigidBody()->CheckSameOwner(shared_from_this()))
		{
			// animator_->PlayRequest("on_damage");
		}
	}
}

void EnemyBase::OnGround(std::shared_ptr<IPhysicsEventReceiver> object)
{
	is_ground_ = TRUE;
	fall_speed_ = 0.f;
	vel_.y = 0.f;
}

void EnemyBase::UnGround()
{
	is_ground_ = FALSE;
}

void EnemyBase::OnDamageFromPlayer(float damage,AttackType type)
{
	auto final_damage = status_container_->TakeDamage(damage,type);

	DamageUIGroup::GetInstance().SpawnEnemyDamageUI(VAdd(pos_,VGet(0.f,5.f,0.f)),final_damage);

	// 体を赤くする
	hit_red_body_->Request(ChangeMethod::kLerp, 0.2f);
}

const bool EnemyBase::GetOnGround() const
{
	return rigid_body_->GetOnGround();
}

std::shared_ptr<StatusContainer> EnemyBase::GetStatusContainer()
{
	return status_container_;
}

std::shared_ptr<RigidBody> EnemyBase::GetRigidBody()
{
	return rigid_body_;
}

const float EnemyBase::GetDeltaTime() const
{
	return time_->GetFPSRate();
}

const VECTOR EnemyBase::GetAttackTargetPos() const
{
	return target_player_pos_;
}

void EnemyBase::UpdateBone()
{
	int hand_bone_num = 0;
	const TCHAR* hand_bone_path = "mixamorig:RightHand";
	hand_bone_num = MV1SearchFrame(handle_, hand_bone_path);
	MATRIX hand_mat = MV1GetFrameLocalWorldMatrix(handle_, hand_bone_num);
	VECTOR right_hand_pos = VectorAssistant::VGetPositionFromMatrix(hand_mat);
	right_hand_pos_ = right_hand_pos;
}