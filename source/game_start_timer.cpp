#include<memory>
#include<unordered_map>
#include"DxLib.h"
#include"game_start_timer.h"
#include"condition_timer.h"
#include<string>
#include"input_manager.h"
#include<functional>
#include"draw_2D.h"
#include"screen_size.h"
#include"FPS.h"
#include"lerp.h"

GameStartTimer::GameStartTimer(bool* game_start)
	: timer_(std::make_shared<ConditionTimer>(1.f))
	, game_image_pos_(VGet(float(kScreenWidth) * 0.5f, float(kScreenHeight) * 0.5f,0))
	, start_image_pos_(VGet(float(kScreenWidth) * 0.5f, float(kScreenHeight) * 0.5f, 0))
	, end_(FALSE)
	, game_start_(game_start)
	, blend_(255.f)
	, start_blend_(0.f)
	, draw_start_(FALSE)
{
	timer_->ReStart();
	InputManager::GetInstance().StopAllInput();
	game_handle_ = LoadGraph("data/ui/game_start/game_ui.png");
	start_handle_ = LoadGraph("data/ui/game_start/start_ui.png");
}

GameStartTimer::~GameStartTimer()
{
	DeleteGraph(game_handle_);
	DeleteGraph(start_handle_);
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
	//if (end_) { return; }
	timer_->Update();
	blend_ = Lerp::Lerpf(blend_, 0, 10.f * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS());
	if (timer_->GetIsEnd())
	{
		// ゲームを開始
		// インプットの受付と敵の行動を開始
		InputManager::GetInstance().StartAllInput();

		// スタート文字の表示
		if (!draw_start_)
		{
			start_blend_ = 255;
			draw_start_ = TRUE;
		}

		start_blend_ = Lerp::Lerpf(start_blend_, 0, 5.f * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS());

		end_ = TRUE;
		*game_start_ = TRUE;
	}

}

void GameStartTimer::Draw()
{
	DrawGame();
	if(timer_->GetIsEnd()){ DrawStart(); }
}

void GameStartTimer::DrawGame()
{
	auto draw_game = [this]() -> void
		{
			Draw2D::RotaGraph(game_image_pos_, 2.f, 0.f, game_handle_, TRUE);
		};
	Draw2D::Blend(draw_game, blend_);
	
}

void GameStartTimer::DrawStart()
{
	auto draw_start = [this]() -> void
		{
			Draw2D::RotaGraph(start_image_pos_, 2.f, 0.f, start_handle_, TRUE);
		};
	Draw2D::Blend(draw_start, start_blend_);
}