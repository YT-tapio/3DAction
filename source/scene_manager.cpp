#include<iostream>
#include<unordered_map>
#include"DxLib.h"
#include"scene_manager.h"
#include"scene_base.h"
#include"game.h"
#include"FPS.h"
#include"color.h"
#include"Debug.h"
#include"input_manager.h"
#include"brain.h"
#include"test_scene.h"

SceneManager::SceneManager()
{
	scene_ = std::make_shared<Game>();
	FPS::GetInstance();
	InputManager::GetInstance();
	Brain::GetInstance();
}


SceneManager::~SceneManager()
{

}

void SceneManager::Update()
{
	/*
	static int a = 1;
	if (CheckHitKey(KEY_INPUT_0))
	{
		if (a == 0)
		{
			scene_ = std::make_shared<Test>();
			scene_->Init();
		}
		a = 1;
	}

	if (CheckHitKey(KEY_INPUT_1))
	{
		if (a == 1)
		{
			scene_ = std::make_shared<Game>();
			scene_->Init();
		}
		a = 0;
	}

	*/
	
	ClearDrawScreen();
	FPS::GetInstance().Update();
	InputManager::GetInstance().Update();
	Debug::GetInstance().Reset();
	Debug::GetInstance().Update();

	scene_->Update();

	scene_->Draw();

	FPS::GetInstance().Wait();
	FPS::GetInstance().SetPrevTime();
	ScreenFlip();
}