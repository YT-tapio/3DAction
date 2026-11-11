#include<functional>
#include"DxLib.h"
#include"chase_main_player.h"
#include<string>
#include<vector>
#include<memory>
#include"input_base.h"
#include"ai_input.h"

ChaseMainPlayer::ChaseMainPlayer(AIInput* input,std::function<VECTOR()> get_onwer_pos, std::function<VECTOR()> get_main_player_pos)
	: input_(input)
	, get_owner_pos_(get_onwer_pos)
	, get_main_player_pos_(get_main_player_pos)
{

}

ChaseMainPlayer::~ChaseMainPlayer()
{

}

void ChaseMainPlayer::Init()
{

}

void ChaseMainPlayer::Entry()
{

}

BehaviorStatus ChaseMainPlayer::Update()
{
	if (get_owner_pos_ == nullptr) { return BehaviorStatus::kFailure; }
	if (get_main_player_pos_ == nullptr) { return BehaviorStatus::kFailure; }
	// メインプレイヤーを追う
	auto owner_pos = get_owner_pos_();
	auto main_player_pos = get_main_player_pos_();

	auto dir = VNorm(VSub(main_player_pos, owner_pos));

	input_->SetStickDir(dir);

	return BehaviorStatus::kComplete;
}

void ChaseMainPlayer::Exit()
{

}