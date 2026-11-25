#include<memory>
#include<string>
#include<vector>
#include"vector_assistant.h"
#include"DxLib.h"
#include"ai_input.h"
#include"player.h"
#include"player_group.h"
#include"status.h"
#include"status_container.h"
#include"enemy_base.h"
#include"attack_info_holder.h"

#include"behavior_tree.h"
#include"node_base.h"
#include"composite_node.h"
#include"selector_node.h"
#include"sequence_node.h"
#include"action_node.h"

#include"behavior_interface.h"
#include"execute_skill.h"
#include"check_skill_can_use.h"
#include"chase.h"
#include"check_near_target.h"
#include"check_inside_target.h"
#include"check_stamina.h"

#include"attack_target_repository.h"
#include"faction.h"
#include"target_selector.h"

AIInput::AIInput(std::weak_ptr<AttackTargetRepository> attack_target_repository)
	: InputBase()
	, get_owner_pos_(nullptr)
	, get_attack_target_pos_(nullptr)
{
	owner_ = nullptr;
	target_selector_ = std::make_shared<TargetSelector>(attack_target_repository, Faction::enemy);
}

AIInput::~AIInput()
{

}

void AIInput::Init()
{
	ResetInfo();
	//この中でbehaviortreeを生成
	MakeBehaviorTree();
	target_selector_->Init();
}

void AIInput::Update()
{
	if (owner_ == nullptr) { return; }
	if (is_stop_) { return; }

	ResetInfo();
	target_selector_->Update();
	if (behavior_tree_ != nullptr) 
	{
		behavior_tree_->Update();
	}
	return;
	//
	
	// メインのプレイヤーについていく
	if (auto player_group = player_group_.lock())
	{
		// 現在のプレイヤーの情報を取得
		auto main_player_pos = *player_group->GetCurrentPlayerHeadPos();
		auto owner_pos = owner_->GetPosition();

		auto dist = VSub(main_player_pos, owner_pos);
		
		// 距離によって変える
		if (VSize(dist) > 15.f)
		{
			move_dir_ = VNorm(dist);
			move_dir_.y = move_dir_.z;
			move_dir_.z = 0.f;

			auto status = owner_->GetStatusContainer();

			if (VSize(dist) > 24.f)
			{
				is_push_dash_ = TRUE;
			}
		}

		if (VSize(dist) < 55.f)
		{
			auto area_object = owner_->GetMyAreaObject();
			for (auto object : area_object)
			{
				if (auto obj = std::dynamic_pointer_cast<EnemyBase>(object.lock()))
				{
					auto info_holder = obj->GetAttackInfoHolder();
					auto attack_info = info_holder->GetAttackInfo();
					is_push_normal_skill_ = TRUE;

					if (attack_info.phase == AttackPhase::kDodgeTiming)
					{
						is_push_avoid_ = TRUE;
					}

					break;
				}
			}
		}


	}
}

void AIInput::SetPlayerGroup(std::weak_ptr<PlayerGroup> player_group)
{
	player_group_ = player_group;
}

void AIInput::SetStickDir(const VECTOR& dir)
{
	move_dir_ = dir;
}

void AIInput::PushSkill(const SkillType& type)
{
	switch (type)
	{
	case SkillType::kNormal:
		is_push_normal_skill_ = TRUE;
		break;

	case SkillType::kStrong:
		is_push_strong_skill_ = TRUE;
		break;

	case SkillType::kAvoid:
		is_push_avoid_ = TRUE;
		break;

	case SkillType::kJump:
		is_push_jump_ = TRUE;
		break;

	}
}

const bool AIInput::CheckIsPlayer() const
{
	return FALSE;
}

const bool AIInput::IsDash() const
{
	return is_push_dash_;
}

const bool AIInput::IsPunch() const
{
	if (is_stop_) { return FALSE; }
	return FALSE;
}

const bool AIInput::IsAvoid() const
{
	return is_push_avoid_;
}

const bool AIInput::IsJump() const
{
	return is_push_jump_;
}

const bool AIInput::IsNormalSkill() const
{
	return is_push_normal_skill_;
}

const bool AIInput::IsStrongSkill() const
{
	return is_push_strong_skill_;
}

const VECTOR AIInput::GetMoveDir() const
{
	VECTOR dir = VectorAssistant::VGetZero();
	if (is_stop_) { return dir; }
	dir = move_dir_;

	return dir;
}

const VECTOR AIInput::GetCameraDir() const
{
	VECTOR dir = VectorAssistant::VGetZero();
	if (is_stop_) { return dir; }
	dir = move_dir_;
	return dir;
}

void AIInput::LoadFile()
{
	//データの読み取り

}

void AIInput::MakeBehaviorTree()
{	

	get_owner_pos_ = [this]() -> VECTOR
		{
			return owner_->GetPosition();
		};

	get_attack_target_pos_ = [this]() -> VECTOR
		{
			return target_selector_->GetAttackTarget()->GetAttackTargetInfo().pos;
		};

	auto get_main_player_pos = [this]() -> VECTOR
		{
			return GetMainPlayerPos();
		};

	auto use_strong_skill_node = MakeExecuteSkillNode(SkillType::kStrong);
	auto use_normal_skill_node = MakeExecuteSkillNode(SkillType::kNormal);
	auto use_avoid_skill_node = MakeExecuteSkillNode(SkillType::kAvoid);
	auto use_jump_skill_node = MakeExecuteSkillNode(SkillType::kJump);
	auto chase_main_player_node = MakeChaseNode(get_main_player_pos);
	auto chase_attack_target_node = MakeChaseNode(get_attack_target_pos_);
	auto check_near_target = MakeCheckNearTargetNode();
	std::vector<std::shared_ptr<NodeBase>> nodes;
	
	auto check_near_node = MakeCheckNearTargetNode();
	//nodes.emplace_back(check_near_node);
	nodes.emplace_back(chase_attack_target_node);
	nodes.emplace_back(check_near_target);
	nodes.emplace_back(use_avoid_skill_node);
	//nodes.emplace_back(use_normal_skill_node);
	//nodes.emplace_back(use_strong_skill_node);
	//nodes.emplace_back(use_avoid_skill_node);
	//nodes.emplace_back(use_jump_skill_node);
	auto first_node = std::make_shared<SequenceNode>(nodes);
	behavior_tree_ = std::make_shared<BehaviorTree>(first_node);
	behavior_tree_->Init();
}

void AIInput::ResetInfo()
{
	is_push_avoid_ = FALSE;
	is_push_dash_ = FALSE;
	is_push_jump_ = FALSE;
	is_push_normal_skill_ = FALSE;
	is_push_strong_skill_ = FALSE;
	is_start_ = FALSE;
	move_dir_ = VectorAssistant::VGetZero();
}

std::shared_ptr<NodeBase> AIInput::MakeExecuteSkillNode(const SkillType& type)
{
	std::shared_ptr<NodeBase> node = nullptr;

	auto get_can_use = [this,type]() -> bool
		{
			return this->owner_->GetSkillCanUse(type);
		};

	auto check_cool_time_node = std::make_shared<ActionNode>(std::make_shared<CheckSkillCanUse>(get_can_use));
	auto skill_node = std::make_shared<ActionNode>(std::make_shared<ExecuteSkill>(this, type));

	std::vector<std::shared_ptr<NodeBase>> nodes;
	
	nodes.emplace_back(check_cool_time_node);
	nodes.emplace_back(skill_node);

	node = std::make_shared<SequenceNode>(nodes);
	return node;
}

std::shared_ptr<NodeBase> AIInput::MakeChaseNode(std::function<VECTOR()> get_target_pos)
{
	std::shared_ptr<NodeBase> node = nullptr;

	std::vector<std::shared_ptr<NodeBase>> chase_nodes;

	auto chase_behavior = std::make_shared<Chase>(this, get_owner_pos_, get_target_pos);
	auto chase_node = std::make_shared<ActionNode>(chase_behavior);
	
	chase_nodes.emplace_back(chase_node);

	//ノードを作成
	node = std::make_shared<SelectorNode>(chase_nodes);

	return node;
}

std::shared_ptr<NodeBase> AIInput::MakeCheckNearTargetNode()
{
	std::shared_ptr<NodeBase> node = nullptr;

	const float kNearDist = 20.f;

	auto check_near = std::make_shared<CheckNearTarget>(target_selector_, get_owner_pos_, kNearDist);
	node = std::make_shared<ActionNode>(check_near);

	return node;
}

std::shared_ptr<NodeBase> AIInput::MakeCheckInsideTarget()
{
	std::shared_ptr<NodeBase> node = nullptr;

	const float kNearDist = 30.f;

	auto behavior = std::make_shared<CheckInsideTarget>(target_selector_, get_owner_pos_, kNearDist);
	node = std::make_shared<ActionNode>(behavior);

	return node;
}

std::shared_ptr<NodeBase> AIInput::MakeAvoidSkillNode()
{
	std::shared_ptr<NodeBase> node = nullptr;

	auto get_current_stamina = [this]() -> float
		{
			return owner_->GetStatusContainer()->GetCurrentStatus().stamina;
		};

	const float kUseStamina = 2.f;

	// 回避をする際の条件
	auto check_stamina_info = std::make_shared<CheckStamina>(get_current_stamina, kUseStamina);
	auto check_stamina_info_node = std::make_shared<ActionNode>(check_stamina_info);
	auto avoid_skill_node = MakeExecuteSkillNode(SkillType::kAvoid);

	std::vector<std::shared_ptr<NodeBase>> nodes;

	nodes.emplace_back(check_stamina_info_node);
	nodes.emplace_back(avoid_skill_node);

	node = std::make_shared<SequenceNode>(nodes);

	return node;
}

VECTOR AIInput::GetMainPlayerPos()
{
	VECTOR main_player_pos = VectorAssistant::VGetZero();

	if (auto player_group = player_group_.lock())
	{
		main_player_pos = player_group->GetCurrentPlayerPos();
	}

	return main_player_pos;
}