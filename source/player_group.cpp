#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include<functional>
#include<string>
#include"DxLib.h"
#include"player_group.h"
#include"player.h"
#include"input_base.h"
#include"player_input.h"
#include"ai_input.h"
#include"input_manager.h"
#include"vector_assistant.h"
#include"player_ui_group.h"
#include"skill_type.h"
#include"player_skill_ui_group.h"
#include"enemy_base.h"
#include"damage_ui_group.h"
#include"damage_ui_group_interface.h"

PlayerGroup::PlayerGroup()
{
	
}

PlayerGroup::~PlayerGroup()
{
	players_.clear();
}

void PlayerGroup::AddPlayerObserver(IPlayerObserver* observer)
{
	for (auto& player : players_)
	{
		player->AddObserver(observer);
	}
}

void PlayerGroup::Awake(VECTOR* camera_dir,std::shared_ptr<IPlayerUIGroup> player_ui_group,std::shared_ptr<EnemyBase> enemy, std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IDamageUIGroup> damage_ui_group)
{
	current_player_head_pos_ = VectorAssistant::VGetZero();
	camera_dir_ = camera_dir;
	//players_.push_back(std::make_shared<Player>(&(*camera_dir_), InputManager::GetInstance().GetPlayer2Input(),"healer"));
	//players_.push_back(std::make_shared<Player>(&(*camera_dir_), InputManager::GetInstance().GetPlayer3Input(), "defender"));
	//players_.push_back(std::make_shared<Player>(&(*camera_dir_), InputManager::GetInstance().GetPlayer3Input(), "attacker2"));
	players_.push_back(std::make_shared<Player>(camera_dir_, InputManager::GetInstance().GetPlayer1Input(), "attacker",player_ui_group,shadow_creater,damage_ui_group));
	
	for (auto player : players_)
	{
		enemy->AddObserver(player.get());
	}
}

void PlayerGroup::Init(std::shared_ptr<PlayerSkillUIGroup> skill_ui_group)
{
	for (auto& player : players_)
	{
		player->Init();
	}
	// メインキャラ(操作しているキャラ)のスキルのクールタイムや使えるか取得
	for (auto player : players_)
	{
		if (std::dynamic_pointer_cast<const PlayerInput>(player->GetInput()))
		{
			auto normal_skill_id = player->GetSkillID(SkillType::kNormal);
			auto normal_skill_cool_time = [player]() ->float {return player->GetSkillCoolTime(SkillType::kNormal); };
			auto normal_skill_can_use = [player]() ->bool {return player->GetSkillCanUse(SkillType::kNormal); };
			auto strong_skill_id = player->GetSkillID(SkillType::kStrong);
			auto strong_skill_cool_time = [player]() ->float {return player->GetSkillCoolTime(SkillType::kStrong); };
			auto strong_skill_can_use = [player]() ->bool {return player->GetSkillCanUse(SkillType::kStrong); };

			skill_ui_group->ChangeSkill(normal_skill_id, normal_skill_cool_time, normal_skill_can_use,
				strong_skill_id, strong_skill_cool_time, strong_skill_can_use);
			break;
		}
	}

}

void PlayerGroup::Update()
{
	CheckCurrentPlayerInfo();
	
	for (auto& player : players_)
	{
		player->Update();
	}
}

void PlayerGroup::End()
{
	players_.clear();
}

void PlayerGroup::LateUpdate()
{
	for (auto& player : players_)
	{
		player->LateUpdate();
	}
}

void PlayerGroup::Stop()
{
	for (auto& player : players_)
	{
		player->SetIsStop(TRUE);
	}
}

void PlayerGroup::Draw()
{
	for (auto& player : players_)
	{
		player->Draw();
	}
}

void PlayerGroup::Debug()
{
	for (auto& player : players_)
	{
		player->Debug();
	}
}

VECTOR* PlayerGroup::GetCurrentPlayerHeadPos()
{
	return &current_player_head_pos_;
}

VECTOR* PlayerGroup::GetCurrentPlayerFrontDir()
{
	return &current_player_front_dir_;
}

VECTOR PlayerGroup::MostNearPlayerPos(const VECTOR& pos)
{
	VECTOR most_near_player_pos = VectorAssistant::VGetZero();
	float most_near_player_dist = -1;	// -1の時は最初のプレイヤーの距離を代入する
	for (auto& player : players_)
	{
		float dist = VSize(VSub(player->GetPosition(), pos));
		if (most_near_player_dist == -1)
		{
			most_near_player_dist = dist;
			most_near_player_pos = player->GetPosition();
			continue;
		}
		if (dist < most_near_player_dist)
		{
			most_near_player_dist = dist;
			most_near_player_pos = player->GetPosition();
		}
	}
	return most_near_player_pos;
}

const int PlayerGroup::GetCurrentPlayerSkillID(SkillType type) const
{
	
	return -1;
}

const float PlayerGroup::GetCurrentPlayerSkillCoolTime(SkillType type) const
{
	return 0.f;
}

const bool PlayerGroup::GetCurrentPlayerSkillCanUse(SkillType type) const
{
	return TRUE;
}

void PlayerGroup::CheckCurrentPlayerInfo()
{
	for (auto& player : players_)
	{
		auto input = std::dynamic_pointer_cast<const PlayerInput>(player->GetInput());
		if (input == nullptr) { continue; }
		current_player_head_pos_ = *player->GetHeadPos();
		current_player_front_dir_ = player->GetFrontDir();
		break;
	}
}
