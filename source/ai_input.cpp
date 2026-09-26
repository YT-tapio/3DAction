#include<memory>
#include<string>
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

AIInput::AIInput()
	: InputBase()
{
	owner_ = nullptr;
}

AIInput::~AIInput()
{

}

void AIInput::Init()
{
	ResetInfo();
	//この中でbehaviortreeを生成
	MakeBehaviorTree();
}

void AIInput::Update()
{
	if (owner_ == nullptr) { return; }
	if (is_stop_) { return; }

	ResetInfo();

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