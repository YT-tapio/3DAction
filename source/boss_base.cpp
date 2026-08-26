#include<memory>
#include<string>
#include<vector>
#include<functional>
#include"DxLib.h"
#include"boss_base.h"
#include"object_base.h"
#include"animator_base.h"
#include"animator_enemy.h"
#include"status.h"
#include"status_container.h"

#include"collider_base.h"
#include"capsule.h"
#include"rigid_body.h"
#include"change_method.h"
#include"hit_red_body.h"
#include"physics.h"

#include"player_group.h"
#include"enemy_ui_group.h"
#include"object_setter.h"

#include"behavior_tree.h"
#include"node_base.h"
#include"action_node.h"
#include"composite_node.h"
#include"sequence_node.h"
#include"selector_node.h"
#include"branch_node.h"
#include"random_node.h"
#include"just_one_node.h"

#include"behavior_base.h"
#include"behavior_status.h"
#include"attack_base.h"
#include"double_punch.h"
#include"disp_attack_range.h"
#include"character_behavior.h"
#include"stamp.h"
#include"jump.h"
#include"area_of_effect_attack.h"
#include"play_sound.h"
#include"tackle.h"
#include"roar_tackle.h"
#include"animation_charge.h"
#include"chase_player.h"
#include"roar.h"
#include"effect_id.h"

#include"time.h"
#include"vector_assistant.h"

#include"shadow_creater_interface.h"

BossBase::BossBase(const VECTOR& pos, bool* game_start,std::shared_ptr<IShadowCreater> shadow_creater)
	: EnemyBase(pos, game_start)
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
		&pos_, TRUE, FALSE, 0.03f, 0.1f);
	fall_speed_ = 0.f;

	VECTOR hp_pos = VectorAssistant::VGet2D(1000.f, 100.f);
	VECTOR hp_size = VectorAssistant::VGet2D(500.f, 50.f);

	status_container_ = std::make_shared<StatusContainer>("zako", hp_pos, hp_size);
	hit_red_body_ = std::make_shared<HitRedBody>(handle_);
	float shadow_size = 7.f;
	shadow_creater->CreateShadow(&pos_, shadow_size);
}

BossBase::~BossBase()
{

}

void BossBase::Init()
{
	// behavior_treeの生成
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
		"double_punch", 0.35f, 0.5f, &double_punch_coll_pos_, 3.0f, 6.f, 1.f);
	std::shared_ptr<NodeBase> double_punch_node = std::make_shared<ActionNode>(double_punch);

	// 上から降ってくるノードを生成
	std::vector<std::shared_ptr<NodeBase>> stump_nodes;

	auto ui_stump_end_function = [this]() -> bool {return rigid_body_->GetIsLanding(); };
	float stump_radius = 60.f;
	stump_nodes.push_back(std::make_shared<ActionNode>
		(std::make_shared<DispAttackRange>(obj_mine, &pos_, VGet(stump_radius, 1.f, stump_radius), ui_stump_end_function,3.f)));

	stump_nodes.push_back(std::make_shared<ActionNode>(std::make_shared<Jump>(mine,
		"jumping_attack", timing, 1.f)));

	stump_nodes.push_back(std::make_shared<ActionNode>
		(std::make_shared<Stamp>(obj_mine, &pos_, stump_radius, "jumping_attack", 2.f)));

	std::shared_ptr<NodeBase> stamp_node = std::make_shared<SequenceNode>(stump_nodes);

	// エフェクトによる攻撃
	std::vector<std::shared_ptr<NodeBase>>  area_of_effect_nodes;
	float area_of_effect_radius = 10.f;
	//float area_of_effect_coll_start_time = 
	// 攻撃
	std::shared_ptr<NodeBase> area_of_effect_node = std::make_shared<ActionNode>(std::make_shared<AreaOfEffectAttack>(
		obj_mine, "charge", 0.f, 0.9f, VectorAssistant::VGetSame(2.f), area_of_effect_radius, EffectID::kAreaOfEffect, 2.f, 1.f));

	// ノード終わりじゃなく当たり判定が終わったら描画させたいよね
	// 終了条件はこのbehaviorが終了しているとき
	auto ui_AoE_end_function = [area_of_effect_node]() -> bool { return area_of_effect_node->GetStatus() == BehaviorStatus::kComplete; };

	// ui表示
	std::shared_ptr<NodeBase> area_of_effect_ui_node = std::make_shared<ActionNode>(std::make_shared<DispAttackRange>(
		obj_mine, &target_player_pos_, VGet(area_of_effect_radius, 1.f, area_of_effect_radius), ui_AoE_end_function,2.f));


	// ui表示から先に入れる
	area_of_effect_nodes.push_back(area_of_effect_ui_node);
	area_of_effect_nodes.push_back(area_of_effect_node);

	std::shared_ptr<NodeBase> tackle_voice_node = std::make_shared<ActionNode>(
		std::make_shared<PlaySound3D>(mine, &pos_, "tackle_voice"));

	std::shared_ptr<NodeBase> tackle_node = std::make_shared<ActionNode>(
		std::make_shared<RoarTackle>(mine,
			std::make_shared<RigidBody>(std::make_shared<Capsule>(10.5f, 18.f, 
				VectorAssistant::VGetZero()), &pos_, FALSE, TRUE, 0.1f, 1.f), "tackle", 1.f, 2.f, 1.f));
	
	std::vector<std::shared_ptr<NodeBase>> tackle_nodes;

	tackle_nodes.emplace_back(tackle_voice_node);
	tackle_nodes.emplace_back(tackle_node);

	// ランダムのnodeに代入
	std::vector<std::shared_ptr<NodeBase>> attack_random_nodes;
	attack_random_nodes.emplace_back(stamp_node);
	//attack_random_nodes.emplace_back(double_punch_node);
	//attack_random_nodes.emplace_back(std::make_shared<SequenceNode>(area_of_effect_nodes));
	attack_random_nodes.emplace_back(std::make_shared<SequenceNode>(tackle_nodes));

	// 追いかけるときのノード
	std::vector<std::shared_ptr<NodeBase>> random_nodes_far;

	std::shared_ptr<NodeBase> radom_attack_node = std::make_shared<RandomNode>(attack_random_nodes);

	target_player_pos_ = PlayerGroup::GetInstance().MostNearPlayerPos(pos_);
	std::shared_ptr<NodeBase> chase_node = std::make_shared<ActionNode>(std::make_shared<ChasePlayer>(obj_mine,
		"run", &target_player_pos_, 0.5f));
	/*------*/

		// エフェクトによる攻撃
	std::vector<std::shared_ptr<NodeBase>>  area_of_effect_nodes2;
	float area_of_effect_radius2 = 10.f;

	// 攻撃
	std::shared_ptr<NodeBase> area_of_effect_node2 = std::make_shared<ActionNode>(std::make_shared<AreaOfEffectAttack>(
		obj_mine, "charge", 0.f, 0.9f, VectorAssistant::VGetSame(2.f), area_of_effect_radius2, EffectID::kAreaOfEffect, 2.f, 1.f));

	// ノード終わりじゃなく当たり判定が終わったら描画させたいよね
	// 終了条件はこのbehaviorが終了しているとき
	auto ui_AoE_end_function2 = [area_of_effect_node2]() -> bool { return area_of_effect_node2->GetStatus() == BehaviorStatus::kComplete; };

	// ui表示
	std::shared_ptr<NodeBase> area_of_effect_ui_node2 = std::make_shared<ActionNode>(std::make_shared<DispAttackRange>(
		obj_mine, &target_player_pos_, VGet(area_of_effect_radius2, 1.f, area_of_effect_radius2), ui_AoE_end_function2,2.f));


	// ui表示から先に入れる
	area_of_effect_nodes2.push_back(area_of_effect_ui_node2);
	area_of_effect_nodes2.push_back(area_of_effect_node2);
	/*-------*/
	random_nodes_far.emplace_back(std::make_shared<SequenceNode>(area_of_effect_nodes2));
	random_nodes_far.emplace_back(chase_node);

	std::shared_ptr<NodeBase> random_far_nodes2 = std::make_shared<RandomNode>(random_nodes_far);

	std::pair<std::shared_ptr<NodeBase>, std::shared_ptr<NodeBase>> nodes_;
	//nodes_.first = random_far_nodes2;
	nodes_.first = random_far_nodes2;
	nodes_.second = radom_attack_node;

	std::function<bool()> condition = [this]()-> bool
		{
			float dist_to_player = VSize(VSub(target_player_pos_, pos_));
			return dist_to_player > 10.f;
		};

	std::shared_ptr<NodeBase> roar_node = std::make_shared<JustOneNode>(std::make_shared<Roar>(obj_mine));

	std::shared_ptr<NodeBase> action_branch_node = std::make_shared<BranchNode>(nodes_,
		condition);
	std::vector<std::shared_ptr<NodeBase>> first_nodes;
	first_nodes.emplace_back(action_branch_node);
	std::shared_ptr<NodeBase> first_node = std::make_shared<SelectorNode>(first_nodes);

	// behavior_treeの生成
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

	animator_ = std::make_shared<AnimatorEnemy>(handle_, "enemy");
	animator_->Init();
	status_container_->Init();
	hit_red_body_->Init();
	// test_behavior_->Init();
	behavior_tree_->Init();
	dir_ = VectorAssistant::VGetDirFromRotY(rot_);
}

void BossBase::LoadFile()
{

}