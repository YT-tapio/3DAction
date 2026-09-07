#include<vector>
#include<memory>
#include<string>
#include<unordered_map>
#include"DxLib.h"

#include"object_base.h"
#include"enemy_base.h"
#include"minion_base.h"
#include"vector_assistant.h"
#include"shadow_creater_interface.h"

#include"animator_base.h"
#include"animator_enemy.h"

#include"player_group.h"

#include"collider_base.h"
#include"capsule.h"

#include"physics.h"
#include"rigid_body.h"

#include"behavior_tree.h"

#include"node_base.h"
#include"composite_node.h"
#include"sequence_node.h"
#include"action_node.h"

#include"behavior_base.h"
#include"chase_player.h"
#include"approach_and_attack.h"

#include"change_method.h"
#include"hit_red_body.h"

#include"status.h"
#include"status_container.h"

#include"object_setter.h"

#include"model_repository.h"

MinionBase::MinionBase(const VECTOR& pos, bool* game_start, std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IEnemyUIGroup> enemy_ui_group, std::shared_ptr<IDamageUIGroup> damage_ui_group,
	std::shared_ptr<IPlayerGroup> player_group, std::shared_ptr<IAttackRangeGroup> attack_range_group)
	: EnemyBase(pos,game_start,enemy_ui_group,damage_ui_group,player_group,attack_range_group)
{
	vel_ = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	target_player_pos_ = VectorAssistant::VGetZero();
	pos_ = pos;
	double_punch_coll_pos_ = VectorAssistant::VGetZero();
	right_hand_pos_ = VectorAssistant::VGetZero();
	scale_ = VectorAssistant::VGetSame(0.1f);
	my_name_ = "";
	handle_ = ModelRepository::GetInstance().GetHandle("zako");
	// handle_ = -1;
	if (handle_ == -1) { printfDx("ì«Ç›çûÇ›ÉGÉâÅ[\n"); }
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(6.5f, 18.f, VectorAssistant::VGetZero()),
		&pos_, TRUE, FALSE, 0.03f, 0.1f);
	fall_speed_ = 0.f;
	animator_ = std::make_shared<AnimatorEnemy>(handle_, "enemy");

	VECTOR hp_pos = VectorAssistant::VGet2D(1000.f, 100.f);
	VECTOR hp_size = VectorAssistant::VGet2D(500.f, 50.f);

	status_container_ = std::make_shared<StatusContainer>("zako_minion", hp_pos, hp_size);
	hit_red_body_ = std::make_shared<HitRedBody>(handle_);
	float shadow_size = 5.f;
	shadow_creater->CreateShadow(&flat_hips_pos_, shadow_size);
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
}

MinionBase::~MinionBase()
{

}

void MinionBase::Init()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("enemy");
	Physics::GetInstance().AddBody(rigid_body_);
	animator_->Init();
	std::shared_ptr<EnemyBase> mine = std::dynamic_pointer_cast<EnemyBase>(shared_from_this());
	target_player_pos_ = player_group_->MostNearPlayerPos(pos_);
	MakeBehaviorTree(mine);
}

void MinionBase::Update()
{
	UpdateBone();
	if (status_container_->GetCurrentStatus().hp <= 0)
	{
		animator_->PlayRequest("death");
	}
	else
	{
		target_player_pos_ = player_group_->MostNearPlayerPos(pos_);
		behavior_tree_->Update();
	}
	
	animator_->Update(time_);
}

void MinionBase::LateUpdate()
{

}

void MinionBase::Draw()
{
	MV1DrawModel(handle_);
}

void MinionBase::Debug()
{

}

void MinionBase::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void MinionBase::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void MinionBase::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void MinionBase::OnGround(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void MinionBase::UnGround()
{

}

void MinionBase::MakeBehaviorTree(std::shared_ptr<EnemyBase> mine)
{
	auto node = MakeChaseNode(mine);
	behavior_tree_ = std::make_shared<BehaviorTree>(node);
}

const bool MinionBase::IsBoss() const
{
	return FALSE;
}

std::shared_ptr<NodeBase> MinionBase::MakeChaseNode(std::shared_ptr<EnemyBase> mine)
{
	std::shared_ptr<NodeBase> chase_node = nullptr;

	auto behavior = std::make_shared<ChasePlayer>(mine, "walk", &target_player_pos_, 0.1f);

	chase_node = std::make_shared<ActionNode>(behavior);

	return chase_node;
}

