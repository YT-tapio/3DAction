#include<iostream>
#include<unordered_map>
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



void SceneManager::Update()
{
	ClearDrawScreen();
	SetLightAmbColor(GetColorF(1.f, 1.f, 1.f, 1.0f));
	FPS::GetInstance().Update();
	InputManager::GetInstance().Update();
	Debug::GetInstance().Reset();
	Debug::GetInstance().Update();
	scene_->Update();
	scene_->Draw();
	ScreenFlip();
	FPS::GetInstance().Wait();
}

void SceneManager::LoadScene(const std::string& next_scene)
{
	if (next_scene == scene_->GetName()) { return; }

	if (next_scene == "title") { scene_ = std::make_shared<Title>(); }
	if (next_scene == "game") { scene_ = std::make_shared<Game>(); }
	//if (next_scene == "result") { scene_ = std::make_shared<Result>(); }

	scene_->Init();
}

void SceneManager::End()
{
	scene_ = nullptr;
}

SceneManager::SceneManager()
{
	scene_ = std::make_shared<Title>();
	FPS::GetInstance();
	InputManager::GetInstance();
	Brain::GetInstance();
}