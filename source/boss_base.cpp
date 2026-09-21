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

#include"model_repository.h"

BossBase::BossBase(const VECTOR& pos, bool* game_start,std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IEnemyUIGroup> enemy_ui_group,
	std::shared_ptr<IDamageUIGroup> damage_ui_group, std::shared_ptr<IPlayerGroup> player_group, std::shared_ptr<IAttackRangeGroup> attack_range_group)
	: EnemyBase(pos, game_start,enemy_ui_group,damage_ui_group,player_group,attack_range_group)
{
	vel_ = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	target_player_pos_ = VectorAssistant::VGetZero();
	pos_ = pos;
	double_punch_coll_pos_ = VectorAssistant::VGetZero();
	right_hand_pos_ = VectorAssistant::VGetZero();
	scale_ = VectorAssistant::VGetSame(0.15f);
	my_name_ = "";
	//handle_ = MV1LoadModel("data/model/enemy/zako/Demon_T_Wiezzorek.mv1");
	handle_ = ModelRepository::GetInstance().GetHandle("zako");
	// handle_ = -1;
	if (handle_ == -1) { printfDx("読み込みエラー\n"); }
	
	fall_speed_ = 0.f;

	VECTOR hp_pos = VectorAssistant::VGet2D(1000.f, 100.f);
	VECTOR hp_size = VectorAssistant::VGet2D(500.f, 50.f);

	status_container_ = std::make_shared<StatusContainer>("zako", hp_pos, hp_size);
	hit_red_body_ = std::make_shared<HitRedBody>(handle_);
	float shadow_size = 7.f;
	shadow_creater->CreateShadow(&flat_hips_pos_, &is_active_,shadow_size);
}

BossBase::~BossBase()
{
	//std::cout << "BossBase" << std::endl;
	if (handle_ != -1)
	{
		MV1DeleteModel(handle_);
		handle_ = -1;
	}
}

void BossBase::Init()
{
	
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
		target_player_pos_ = player_group_->MostNearPlayerPos(pos_);
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
			//Brain::GetInstance().ChangeCamera("boss_phase2");
			//printfDx("フェーズ切り替え\n");
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

const bool BossBase::IsBoss() const
{
	return TRUE;
}
