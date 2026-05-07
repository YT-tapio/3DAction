#include<iostream>
#include<string>
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
#include"behavior_base.h"
#include"double_punch.h"
#include"jumping_attack.h"
#include"jump.h"
#include"stamp.h"
#include"color.h"
#include"node_base.h"
#include"composite_node.h"
#include"sequence_node.h"
#include"action_node.h"

EnemyBase::EnemyBase(const VECTOR& pos)
	: CharacterBase("enemy")
	, IPhysicsEventReceiver()
{
	vel_ = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	pos_ = pos;
	double_punch_coll_pos_ = VectorAssistant::VGetZero();
	right_hand_pos_ = VectorAssistant::VGetZero();
	scale_ = VectorAssistant::VGetSame(0.15f);
	my_name_ = "";
	handle_ = MV1LoadModel("data/model/enemy/zako/Demon_T_Wiezzorek.mv1");
	if (handle_ == -1) { printfDx("ì«Ç›çûÇ›ÉGÉâÅ[\n"); }
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Capsule>(5.5f, 18.f, VectorAssistant::VGetZero()), 
		&pos_, TRUE, FALSE, 0.03f,0.1f);
	fall_speed_ = 0.f;

}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Init()
{
	

	rigid_body_->Init(weak_from_this());
	// physicsÇÃìoò^
	Physics::GetInstance().AddBody(rigid_body_);
	// setterÇ÷ÇÃìoò^
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
	auto physics_mine = shared_from_this();
	auto mine = std::dynamic_pointer_cast<EnemyBase>(physics_mine);
	std::shared_ptr<ObjectBase> obj_mine = mine;

	std::vector<std::shared_ptr<NodeBase>> nodes;
	nodes.push_back(std::make_shared<ActionNode>(std::make_shared<Jump>(obj_mine,
		"jump_attack", 0.38f, 1.f)));

	nodes.push_back(std::make_shared<ActionNode>
		(std::make_shared<Stamp>(obj_mine, &pos_, 5.f)));

	std::shared_ptr<NodeBase> first_node = std::make_shared<SequenceNode>(nodes);
	behavior_tree_ = std::make_shared<BehaviorTree>(first_node);

	UpdateBone();
	/*
	test_behavior_ = std::make_shared<DoublePunch>(std::dynamic_pointer_cast<ObjectBase>(mine),
		"double_punch", 0.35f, 0.5f, &double_punch_coll_pos_, 3.0f, 6.f);
	*/
	/*
	test_behavior_ = std::make_shared<JumpingAttack>
		(obj_mine, &pos_, 0.5f, 0.75f, "jumping_attack");
	*/
	test_behavior_ = std::make_shared<Jump>
		(obj_mine, "jumping_attack" , 0.38f, 1.f);
	

	animator_ = std::make_shared<AnimatorEnemy>(handle_, std::dynamic_pointer_cast<EnemyBase>(mine),"enemy");
	animator_->Init();
	test_behavior_->Init();
	dir_ = VectorAssistant::VGetDirFromRotY(rot_);
}

void EnemyBase::Update()
{
	VECTOR dir = VectorAssistant::VGetZero();
	//dir_ = VectorAssistant::VGetZero();
	// vel_ = dir;

	double_punch_coll_pos_ = VAdd(pos_, VScale(dir_, 5.f));

	rigid_body_->SetTargetVelocity(vel_);
	animator_->Update();
	UpdateBone();
	// test_behavior_->Update();
	behavior_tree_->Update();
}

void EnemyBase::LateUpdate()
{

}

void EnemyBase::Draw()
{
	MV1DrawModel(handle_);
}

void EnemyBase::Debug()
{
	rigid_body_->Debug();
	// test_behavior_->Debug();
}

void EnemyBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> obj)
{
	auto punch = std::dynamic_pointer_cast<Punch>(obj);
	if (punch != nullptr)
	{
		if (std::dynamic_pointer_cast<EnemyBase>(punch->GetOwner().lock()) == nullptr)
		{
			animator_->PlayRequest("on_damage");
			//printfDx("Ç¢Çƒ\n");
		}
	}

}

void EnemyBase::OnGround(std::shared_ptr<IPhysicsEventReceiver> object)
{
	is_ground_ = TRUE;
	fall_speed_ = 0.f;
	vel_.y = 0.f;
}

void EnemyBase::UnGround(std::shared_ptr<IPhysicsEventReceiver> object)
{
	is_ground_ = FALSE;
}

const bool EnemyBase::GetOnGround() const
{
	return rigid_body_->GetOnGround();
}

std::shared_ptr<RigidBody> EnemyBase::GetRigidBody()
{
	return rigid_body_;
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