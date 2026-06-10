#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include"DxLib.h"
#include"player_group.h"
#include"player.h"
#include"input_base.h"
#include"player_input.h"
#include"ai_input.h"
#include"input_manager.h"
#include"vector_assistant.h"

PlayerGroup::PlayerGroup()
{

}

void PlayerGroup::Awake(VECTOR* camera_dir)
{
	current_player_head_pos_ = VectorAssistant::VGetZero();
	camera_dir_ = camera_dir;
	players_.push_back(std::make_shared<Player>(&(*camera_dir_), InputManager::GetInstance().GetPlayer1Input(), "attacker"));
	// players_.push_back(std::make_shared<Player>(&(*camera_dir_), InputManager::GetInstance().GetPlayer2Input(),"healer"));
	// players_.push_back(std::make_shared<Player>(&(*camera_dir_), InputManager::GetInstance().GetPlayer3Input(), "defender"));
	// players_.push_back(std::make_shared<Player>(&(*camera_dir_), InputManager::GetInstance().GetPlayer3Input(), "attacker2"));
	
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
	CheckCurrentPlayerHeadPos();

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

VECTOR PlayerGroup::MostNearPlayerPos(const VECTOR& pos)
{
	VECTOR most_near_player_pos = VectorAssistant::VGetZero();
	float most_near_player_dist = -1;	// -1‚ÌŽž‚ÍÅ‰‚ÌƒvƒŒƒCƒ„[‚Ì‹——£‚ð‘ã“ü‚·‚é
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


void PlayerGroup::CheckCurrentPlayerHeadPos()
{
	for (auto& player : players_)
	{
		auto input = std::dynamic_pointer_cast<const PlayerInput>(player->GetInput());
		if (input == nullptr) { continue; }
		current_player_head_pos_ = *player->GetHeadPos();
		break;
	}
}
