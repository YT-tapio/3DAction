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
#include"check_phase_node.h"
#include"check_count_node.h"

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
#include"approach_and_attack.h"

#include"time.h"
#include"vector_assistant.h"

#include"shadow_creater_interface.h"
#include<unordered_map>
#include"enemy_cool_time_controller.h"

#include"load_csv_file.h"

#include"brain.h"
#include"enemy_ui_group_interface.h"

BossBase::BossBase(const VECTOR& pos, bool* game_start,std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IEnemyUIGroup> enemy_ui_group,std::shared_ptr<IDamageUIGroup> damage_ui_group)
	: EnemyBase(pos, game_start,enemy_ui_group,damage_ui_group)
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
	shadow_creater->CreateShadow(&flat_hips_pos_, shadow_size);
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
	target_player_pos_ = PlayerGroup::GetInstance().MostNearPlayerPos(pos_);
	auto physics_mine = shared_from_this();
	auto mine = std::dynamic_pointer_cast<EnemyBase>(physics_mine);
	std::shared_ptr<ObjectBase> obj_mine = mine;

	
	
	MakeBehaviorTree(mine);

	std::function<int()> get_base_hp = [this]()-> int
		{
			return static_cast<int>(status_container_->GetBaseStatus().hp);
		};
	std::function<int()> get_current_hp = [this]()-> int
		{
			return static_cast<int>(status_container_->GetCurrentStatus().hp);
		};

	// uiを作成
	enemy_ui_group_->MakeStatusUI(get_base_hp, get_current_hp, "zako");

	UpdateBone();

	animator_ = std::make_shared<AnimatorEnemy>(handle_, "enemy");
	time_->Init();
	animator_->Init();
	status_container_->Init();
	hit_red_body_->Init();
	behavior_tree_->Init();
	dir_ = VectorAssistant::VGetDirFromRotY(rot_);
}

void BossBase::Update()
{
	time_->Update();
	cool_time_->Update();
	UpdatePhase();
	if (status_container_->GetCurrentStatus().hp <= 0)
	{
		animator_->PlayRequest("death");
	}
	else
	{
		// 一番近いプレイヤーの位置を取得
		target_player_pos_ = PlayerGroup::GetInstance().MostNearPlayerPos(pos_);
		VECTOR dir = VectorAssistant::VGetZero();

		double_punch_coll_pos_ = VAdd(pos_, VScale(dir_, 5.f));

		rigid_body_->SetTargetVelocity(vel_);

		if (*game_start_)
		{
			if (TRUE) { behavior_tree_->Update(); }
		}
	}
	
	animator_->Update(time_);
	UpdateBone();
	hit_red_body_->Update();
}

void BossBase::MakeBehaviorTree(std::shared_ptr<EnemyBase> mine)
{
	auto current_phase = [this]() -> Phase
		{
			return phase_;
		};

	auto can_execute = [this](const std::string& name) -> bool
		{
			return cool_time_->GetIsEnd(name);
		};

	// 両手パンチのノードを生成
	auto conbo_attack_node = MakeComboAttackNode(mine, current_phase);
	// スタンプ
	auto stamp_node = MakeStampNode(mine, current_phase);
	// 魔法攻撃
	auto magic_node = MakeMagicNode(mine, current_phase);
	// タックル
	auto tackle_node = MakeTackleNode(mine, current_phase);

	// ランダムのnodeに代入
	std::vector<std::shared_ptr<NodeBase>> attack_random_nodes;
	attack_random_nodes.emplace_back(conbo_attack_node);
	attack_random_nodes.emplace_back(stamp_node);
	//attack_random_nodes.emplace_back(magic_node);
	attack_random_nodes.emplace_back(tackle_node);

	// 追いかけるときのノード
	std::vector<std::shared_ptr<NodeBase>> random_nodes_far;
	auto radom_attack_node = std::make_shared<RandomNode>(attack_random_nodes);

	// エフェクトによる攻撃
	auto chase_node = MakeChaseNode(mine);
	auto far_magic_node = MakeMagicNode(mine,current_phase);
	/*-------*/
	//random_nodes_far.emplace_back(far_magic_node);
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
	std::shared_ptr<NodeBase> roar_node = MakeRoarNode(mine);

	std::shared_ptr<NodeBase> action_branch_node = std::make_shared<BranchNode>(nodes_,
		condition);
	std::vector<std::shared_ptr<NodeBase>> first_nodes;
	first_nodes.emplace_back(roar_node);
	first_nodes.emplace_back(action_branch_node);
	std::shared_ptr<NodeBase> first_node = std::make_shared<SelectorNode>(first_nodes);

	// behavior_treeの生成
	behavior_tree_ = std::make_shared<BehaviorTree>(first_node);
}

void BossBase::UpdatePhase()
{

	auto current_status		= status_container_->GetCurrentStatus();
	auto base_status		= status_container_->GetBaseStatus();

	float hp_ratio = current_status.hp / base_status.hp;

	switch (phase_)
	{
	case Phase::first:
		if (hp_ratio < 0.8f) 
		{
			// カメラを切り替える
			Brain::GetInstance().ChangeCamera("boss_phase2");
			printfDx("フェーズ切り替え\n");
			phase_ = Phase::second;
		}

		break;
	case Phase::second:

		if (hp_ratio < 0.5f) { phase_ = Phase::third; }

		break;

	case Phase::third:

		break;
	}


}

void BossBase::LoadFile()
{

}

std::shared_ptr<NodeBase> BossBase::MakeMagicNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase)
{
	std::shared_ptr<NodeBase> node_;
	// エフェクトによる攻撃
	std::vector<std::shared_ptr<NodeBase>>  area_of_effect_nodes;
	float area_of_effect_radius = 10.f;
	// 攻撃
	
	std::shared_ptr<BehaviorBase> behavior = std::make_shared<AreaOfEffectAttack>(
		mine, "charge", 0.f, 0.9f, VectorAssistant::VGetSame(2.f), area_of_effect_radius, EffectID::kAreaOfEffect, 2.f, 1.f);
	std::shared_ptr<NodeBase> area_of_effect_node = std::make_shared<ActionNode>(behavior);

	std::shared_ptr<NodeBase> count_node = std::make_shared<CheckCountNode>(1);

	// ノード終わりじゃなく当たり判定が終わったら描画させたいよね
	// 終了条件はこのbehaviorが終了しているとき
	auto ui_AoE_end_function = [area_of_effect_node]() -> bool { return area_of_effect_node->GetStatus() == BehaviorStatus::kComplete; };

	auto check_phase_node = std::make_shared<CheckPhaseNode>(Phase::first, current_phase);

	std::shared_ptr<BehaviorBase> range = std::make_shared<DispAttackRange>(
		mine, &target_player_pos_, VGet(area_of_effect_radius, 1.f, area_of_effect_radius), ui_AoE_end_function, 2.f);

	// ui表示
	std::shared_ptr<NodeBase> area_of_effect_ui_node = std::make_shared<ActionNode>(range);

	// ui表示から先に入れる
	area_of_effect_nodes.push_back(check_phase_node);
	area_of_effect_nodes.push_back(count_node);
	area_of_effect_nodes.push_back(area_of_effect_ui_node);
	area_of_effect_nodes.push_back(area_of_effect_node);

	node_ = std::make_shared<SequenceNode>(area_of_effect_nodes);

	return node_;
}

std::shared_ptr<NodeBase> BossBase::MakeTackleNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase)
{
	std::shared_ptr<NodeBase> node;

	std::shared_ptr<NodeBase> tackle_voice_node = std::make_shared<ActionNode>(
		std::make_shared<PlaySound3D>(mine, &pos_, "tackle_voice"));

	std::shared_ptr<ColliderBase> collider = std::make_shared<Capsule>(10.5f, 18.f,
		VectorAssistant::VGetZero());

	std::shared_ptr<RigidBody> rigid_body = std::make_shared<RigidBody>(collider, &pos_, FALSE, TRUE, 0.1f, 1.f);
	std::shared_ptr<BehaviorBase> tackle = std::make_shared<RoarTackle>(mine, rigid_body, "tackle", 1.f, 2.f, 1.f);
	std::shared_ptr<NodeBase> tackle_node = std::make_shared<ActionNode>(tackle);
	auto check_phase_node = std::make_shared<CheckPhaseNode>(Phase::third, current_phase);
	std::vector<std::shared_ptr<NodeBase>> tackle_nodes;
	tackle_nodes.emplace_back(check_phase_node);
	tackle_nodes.emplace_back(tackle_voice_node);
	tackle_nodes.emplace_back(tackle_node);

	node = std::make_shared<SequenceNode>(tackle_nodes);

	return node;
}

std::shared_ptr<NodeBase> BossBase::MakeStampNode(std::shared_ptr<EnemyBase> mine,std::function<Phase()> current_phase)
{
	std::shared_ptr<NodeBase> node;

	// 上から降ってくるノードを生成
	std::vector<std::shared_ptr<NodeBase>> stump_nodes;

	std::pair<float, float> timing;
	timing.first = 0.38f;
	timing.second = 0.45f;

	float stump_radius = 60.f;
	
	auto phase_node = std::make_shared<CheckPhaseNode>(Phase::second, current_phase);

	// ジャンプ
	auto jump = std::make_shared<Jump>(mine, "jumping_attack", timing, 1.f);
	// ジャンプノード
	auto jump_action_node = std::make_shared<ActionNode>(jump);
	// スタンプ
	auto stamp = std::make_shared<Stamp>(mine, &pos_, stump_radius, "jumping_attack", 2.f);
	// スタンプノード
	auto stamp_action_node = std::make_shared<ActionNode>(stamp);

	auto ui_stump_end_function = [this]() -> bool
		{
			if (animator_->GetRatio("jumping_attack") > 0.5f)
			{
				return rigid_body_->GetIsLanding();
			}
			return FALSE;
		};

	auto disp_range = std::make_shared<DispAttackRange>(mine, &pos_, VGet(stump_radius, 1.f, stump_radius), ui_stump_end_function, 3.f);
	auto stamp_ui_node = std::make_shared<ActionNode>(disp_range);
	stump_nodes.push_back(phase_node);
	stump_nodes.push_back(stamp_ui_node);
	stump_nodes.push_back(jump_action_node);
	stump_nodes.push_back(stamp_action_node);

	node = std::make_shared<SequenceNode>(stump_nodes);

	return node;
}

std::shared_ptr<NodeBase> BossBase::MakeDoublePunchNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase)
{
	std::shared_ptr<NodeBase> node = nullptr;

	std::shared_ptr<BehaviorBase> double_punch = std::make_shared<DoublePunch>(mine,
		"double_punch", 0.35f, 0.5f, &double_punch_coll_pos_, 3.0f, 6.f, 1.f);
	std::shared_ptr<NodeBase> double_punch_node = std::make_shared<ActionNode>(double_punch);
	node = double_punch_node;
	return node;
}

std::shared_ptr<NodeBase> BossBase::MakeComboAttackNode(std::shared_ptr<EnemyBase> mine, std::function<Phase()> current_phase)
{
	std::shared_ptr<NodeBase> node = nullptr;

	const std::string file_path = "data/csv/enemies/zako/behavior/combo_datas.csv";

	auto datas = LoadCSVFile::GetInstance().GetData(file_path, 1);

	std::vector<std::shared_ptr<BehaviorBase>> combos;

	int current_index = 0;
	for (int i = 0; i < datas.indices.size(); i++)
	{
		auto min_coll_ratio = stof(datas.string_datas[current_index]);
		current_index++;
		auto max_coll_ratio = stof(datas.string_datas[current_index]);
		current_index++;
		auto damage_rate = stof(datas.string_datas[current_index]);
		current_index++;
		auto my_anim_name = datas.string_datas[current_index];
		current_index++;
		auto approach_timing = stof(datas.string_datas[current_index]);
		current_index++;
		auto approach_speed = stof(datas.string_datas[current_index]);
		current_index++;
		auto collider_tag = datas.string_datas[current_index];
		current_index++;
		combos.emplace_back(std::make_shared<ApproachAndAttack>(mine, min_coll_ratio,
			max_coll_ratio, damage_rate, my_anim_name, approach_timing, approach_speed, collider_tag));
	}

	std::vector<std::shared_ptr<NodeBase>> combo_attack_nodes;

	for (auto& combo : combos)
	{
		combo_attack_nodes.emplace_back(std::make_shared<ActionNode>(combo));
	}

	node = std::make_shared<SequenceNode>(combo_attack_nodes);

	return node;
}

std::shared_ptr<NodeBase> BossBase::MakeChaseNode(std::shared_ptr<EnemyBase> mine)
{
	std::shared_ptr<NodeBase> node = nullptr;

	auto chase_player = std::make_shared<ChasePlayer>(mine,"run", &target_player_pos_, 0.5f);
	node = std::make_shared<ActionNode>(chase_player);

	return node;
}

std::shared_ptr<NodeBase> BossBase::MakeRoarNode(std::shared_ptr<EnemyBase> mine)
{
	std::shared_ptr<NodeBase> node = nullptr;
	
	std::vector<std::shared_ptr<NodeBase>> roar_nodes;

	auto roar = std::make_shared<Roar>(mine);

	auto roar_node = std::make_shared<ActionNode>(roar);
	auto just_one_node = std::make_shared<JustOneNode>();

	roar_nodes.emplace_back(just_one_node);
	roar_nodes.emplace_back(roar_node);

	node = std::make_shared<SequenceNode>(roar_nodes);

	return node;
}