#include<iostream>
#include"DxLib.h"
#include"scene_manager.h"
#include"scene_base.h"
#include"game.h"
#include"FPS.h"
#include"color.h"
#include"Debug.h"

SceneManager::SceneManager()
{
	scene_ = std::make_shared<Game>();

	FPS::GetInstance();
}


SceneManager::~SceneManager()
{

}

void SceneManager::Update()
{

	FPS::GetInstance().Update();
	Debug::GetInstance().Reset();
	Debug::GetInstance().Update();

	scene_->Update();

	ClearDrawScreen();

	scene_->Draw();

	ScreenFlip();

	FPS::GetInstance().Wait();
	FPS::GetInstance().SetPrevTime();

}