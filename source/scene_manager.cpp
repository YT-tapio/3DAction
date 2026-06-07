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
	ClearDrawScreen();
	SetLightAmbColor(GetColorF(1.f, 1.f, 1.f, 1.0f));
	FPS::GetInstance().Update();
	InputManager::GetInstance().Update();
	/*
	if (CheckHitKey(KEY_INPUT_L) && scene_->GetName() == "game")
	{
		scene_ = std::make_shared<Test>(); 
		scene_->Init();
	}
	if (CheckHitKey(KEY_INPUT_P) && scene_->GetName() == "test") 
	{
		scene_ = std::make_shared<Game>(); 
		scene_->Init();
	}
	*/
	
	Debug::GetInstance().Reset();
	Debug::GetInstance().Update();
	scene_->Update();
	scene_->Draw();
	// FPS::GetInstance().Debug();
	ScreenFlip();
	FPS::GetInstance().Wait();
}