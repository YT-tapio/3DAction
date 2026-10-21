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
#include"enemy_controller.h"
#include"status.h"
#include"status_container.h"
#include"player_observer_interface.h"
#include"brain.h"

PlayerGroup::PlayerGroup()
	: is_death_all_player_(FALSE)
{
	
}

PlayerGroup::~PlayerGroup()
{
	player_observers_.clear();
	players_.clear();
}

void PlayerGroup::AddPlayerObserver(IPlayerObserver* observer)
{
	for (auto& player : players_)
	{
		player->AddObserver(observer);
	}
	player_observers_.emplace_back(observer);
}

void PlayerGroup::Awake(VECTOR* camera_dir,std::shared_ptr<IPlayerUIController> player_ui_controller, std::shared_ptr<IEnemyController> enemy_controller, std::shared_ptr<IShadowCreater> shadow_creater, std::shared_ptr<IDamageUIGroup> damage_ui_group)
{
	current_player_head_pos_ = VectorAssistant::VGetZero();
	camera_dir_ = camera_dir;
	players_.push_back(std::make_shared<Player>(camera_dir_, InputManager::GetInstance().GetPlayer1Input(), "attacker", player_ui_controller, shadow_creater, damage_ui_group));
	players_.push_back(std::make_shared<Player>(camera_dir_, InputManager::GetInstance().GetPlayer2Input(), "healer", player_ui_controller, shadow_creater, damage_ui_group));
	
	// スタミナを生成
	for (auto player : players_)
	{
		enemy_controller->AddBossObserver(player.get());
	}
}

void PlayerGroup::Init()
{
	for (auto& player : players_)
	{
		player->Init();
	}
}

void PlayerGroup::Update()
{
	bool is_death_all_player = TRUE;
	CheckCurrentPlayerInfo();

	for (auto& player : players_)
	{
		player->Update();

		if (is_death_all_player)
		{
			// プレイヤーがHpが0かをチェック
			is_death_all_player = CheckDeathPlayer(player);
		}
	}

	if (is_death_all_player)
	{
		if (!is_death_all_player_)
		{
			for (auto observer : player_observers_)
			{
				observer->OnPlayerDeath();
			}
			Brain::GetInstance().ChangeCamera("lose");
			is_death_all_player_ = TRUE;
		}
		
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

VECTOR PlayerGroup::GetPlayerPos(const std::string& name)
{
	VECTOR player_pos = VectorAssistant::VGetZero();
	for (auto& player : players_)
	{
		if (player->GetName() == name)
		{
			//printfDx("%s\n", name.c_str());
			player_pos = player->GetPosition();
			return player_pos;
		}
	}
	return player_pos;

}

VECTOR PlayerGroup::MostNearPlayerPos(const VECTOR& pos)
{
	VECTOR most_near_player_pos = VectorAssistant::VGetZero();
	float most_near_player_dist = -1;	// -1の時は最初のプレイヤーの距離を代入する
	for (auto& player : players_)
	{
		// プレイヤーが生きていないのなら回さない
		if (CheckDeathPlayer(player)) { continue; }

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

std::string PlayerGroup::MostNearPlayerName(const VECTOR& pos)
{
	std::string most_near_player_name = "none";
	float most_near_player_dist = -1;	// -1の時は最初のプレイヤーの距離を代入する
	std::shared_ptr<Player> most_near_player = nullptr;
	for (auto& player : players_)
	{
		if (CheckDeathPlayer(player)) { continue; }

		float dist = VSize(VSub(player->GetPosition(), pos));
		if (most_near_player_dist == -1)
		{
			most_near_player_dist = dist;
			most_near_player_name = player->GetName();
			most_near_player = player;
			continue;
		}
		if (dist < most_near_player_dist)
		{
			most_near_player_dist = dist;
			most_near_player_name = player->GetName();
			most_near_player = player;
		}
	}

	return most_near_player_name;
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

bool PlayerGroup::CheckDeathPlayer(std::shared_ptr<Player> player)
{
	auto status = player->GetStatusContainer()->GetCurrentStatus();
	return status.hp == 0.f;
}