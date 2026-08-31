#include<memory>
#include<string>
#include"game_to_next_scene.h"
#include"DxLib.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"scene_manager.h"
#include"fade.h"
#include<unordered_map>
#include"input_manager.h"
#include"input_base.h"
#include"sound_manager.h"


GameToNextScene::GameToNextScene()
	: timer_(std::make_shared<VariableTimer>(1.f))
	, is_active_(FALSE)
	, next_scene_("nothing")
{
	timer_->Init();

	// ボタンの作成
	
}

GameToNextScene::~GameToNextScene()
{

}

void GameToNextScene::Init()
{
	timer_->Init();
}

bool GameToNextScene::Update()
{
	if (!is_active_) { return FALSE; }
	timer_->Update();

	if (timer_->GetIsEnd() && next_scene_ == "nothing")
	{
		//ボタンが押されたのを検知
		bool is_push = FALSE;
		if(InputManager::GetInstance().GetMainPlayerInput()->Retry())
		{
			next_scene_ = "load";
			is_push = TRUE;
			SoundManager::GetInstance().Play2DSound("go_game");
		}

		if (InputManager::GetInstance().GetMainPlayerInput()->GameToTitle())
		{
			next_scene_ = "title";
			is_push = TRUE;
			SoundManager::GetInstance().Play2DSound("go_title");
		}

		if (is_push)
		{
			Fade::GetInstance().StartFadeIn(1.f, FadeColorType::kBlack);
		}
	}

	if (Fade::GetInstance().IsFinished())
	{
		SceneManager::GetInstance().LoadScene(next_scene_);
		return TRUE;
	}
	return FALSE;
}

void GameToNextScene::OnPlayerDeath()
{
	is_active_ = TRUE;
	timer_->Stop();
	timer_->ChangeMaxTime(3.f);
	timer_->ReStart();
}

void GameToNextScene::OnEnemyDeath()
{
	is_active_ = TRUE;
	timer_->Stop();
	timer_->ChangeMaxTime(5.f);
	timer_->ReStart();
}
