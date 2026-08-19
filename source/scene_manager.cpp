#include<iostream>
#include<unordered_map>
#include<functional>
#include"DxLib.h"
#include"scene_manager.h"
#include"scene_base.h"
#include"game.h"
#include"title.h"
#include"FPS.h"
#include"color.h"
#include"Debug.h"
#include"input_manager.h"
#include"brain.h"
#include"test_scene.h"
#include"result.h"
#include"sound_manager.h"
#include"fade.h"
#include"load.h"

void SceneManager::Update()
{
	ClearDrawScreen();
	SetLightAmbColor(GetColorF(1.f, 1.f, 1.f, 1.0f));
	FPS::GetInstance().Update();
	InputManager::GetInstance().Update();
	Debug::GetInstance().Reset();
	Debug::GetInstance().Update();
	if (!is_change_)
	{
		scene_->Update();
		Fade::GetInstance().Update();
	}
	else
	{
		is_change_ = FALSE;
	}
	
	scene_->Draw();
	Fade::GetInstance().Draw();

	//DrawString(100, 860, "Escを押すとゲーム終了", GetColor(255, 0, 0));
	ScreenFlip();
	FPS::GetInstance().Wait();
	
}

bool SceneManager::LoadScene(const std::string& next_scene)
{
	if (next_scene == scene_->GetName()) { return FALSE; }
	bool check = FALSE;
	if (next_scene == "title") 
	{ 
		scene_ = std::make_shared<Title>();
		check = TRUE;
	}
	if (next_scene == "game") 
	{ 
		scene_ = std::make_shared<Game>();
		check = TRUE;
	}
	if (next_scene == "result") 
	{ 
		scene_ = std::make_shared<Result>();
		check = TRUE;
	}
	if (next_scene == "load") 
	{
		std::string next_scene_name = scene_->GetName();
		scene_ = std::make_shared<Load>(next_scene_name);
		check = TRUE;
	}

	if (!check)
	{
		printfDx("そのようなシーンは存在しません\n");
	}

	scene_->Init();
	is_change_ = TRUE;
	return TRUE;
}

void SceneManager::End()
{
	scene_ = nullptr;
}

SceneManager::SceneManager()
{
	SoundManager::GetInstance().Load();
	FPS::GetInstance();
	InputManager::GetInstance();
	Brain::GetInstance();
	Fade::GetInstance().Awake();
	//Fade::GetInstance().StartFadeOut(1.f);
	scene_ = std::make_shared<Title>();
	is_change_ = FALSE;
}