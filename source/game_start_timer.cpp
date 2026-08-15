#include<memory>
#include<unordered_map>
#include"DxLib.h"
#include"game_start_timer.h"
#include"condition_timer.h"
#include"input_manager.h"

GameStartTimer::GameStartTimer()
	: timer_(std::make_shared<ConditionTimer>(3.f))
	, end_(FALSE)
{
	timer_->ReStart();
	InputManager::GetInstance().StopAllInput();
}

GameStartTimer::~GameStartTimer()
{

}

void GameStartTimer::Init()
{
	timer_->Init();
	timer_->ReStart();
	end_ = FALSE;
	InputManager::GetInstance().StopAllInput();
}

void GameStartTimer::Update()
{
	if (end_) { return; }
	timer_->Update();

	if (timer_->GetIsEnd())
	{
		// ゲームを開始
		// インプットの受付と敵の行動を開始
		InputManager::GetInstance().StartAllInput();

		// スタート文字の表示


		end_ = TRUE;
	}

}