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
	players_.push_back(std::make_shared<Player>(&(*camera_dir_), InputManager::GetInstance().GetAIInput(), "attacker"));
	//players_.push_back(std::make_shared<Player>(&camera_->dir_, InputManager::GetInstance().GetAIInput2(),"healer"));
	players_.push_back(std::make_shared<Player>(&(*camera_dir_), InputManager::GetInstance().GetPlayerInput(), "defender"));
	//Init();
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
