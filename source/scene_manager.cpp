#include<iostream>
#include"DxLib.h"
#include"scene_manager.h"
#include"scene_base.h"
#include"game.h"
#include"FPS.h"
#include"color.h"

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

	scene_->Update();

	ClearDrawScreen();

	scene_->Draw();
	DrawString(100, 100, "•`‰æ¬Œ÷", Color::kWhite);

	ScreenFlip();

	FPS::GetInstance().Wait();
	FPS::GetInstance().SetPrevTime();

}