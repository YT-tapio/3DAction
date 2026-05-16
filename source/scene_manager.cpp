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