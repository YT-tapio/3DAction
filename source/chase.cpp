#include<functional>
#include"DxLib.h"
#include"chase.h"
#include<string>
#include<vector>
#include<memory>
#include"input_base.h"
#include"ai_input.h"

Chase::Chase(AIInput* input,std::function<VECTOR()> get_onwer_pos, std::function<VECTOR()> get_target_pos)
	: input_(input)
	, get_owner_pos_(get_onwer_pos)
	, get_target_pos_(get_target_pos)
{

}

Chase::~Chase()
{

}

void Chase::Init()
{

}

void Chase::Entry()
{

}

BehaviorStatus Chase::Update()
{
	if (get_owner_pos_ == nullptr) { return BehaviorStatus::kFailure; }
	if (get_target_pos_ == nullptr) { return BehaviorStatus::kFailure; }
	// メインプレイヤーを追う
	auto owner_pos = get_owner_pos_();
	auto target_pos = get_target_pos_();

	auto dist = VSub(target_pos, owner_pos);
	// inputに合わせる
	dist.y = dist.z;
	dist.z = 0.f;
	auto dir = VNorm(dist);

	input_->SetStickDir(dir);

	return BehaviorStatus::kComplete;
}

void Chase::Exit()
{

}