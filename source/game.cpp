#include<iostream>
#include<memory>
#include"DxLib.h"
#include"game.h"
#include"camera.h"
#include"object_base.h"
#include"player.h"
#include"stage.h"
#include"Debug.h"
#include"physics.h"

Game::Game()
	: SceneBase()
{
	camera_ = std::make_shared<Camera>();

	objects_.push_back(std::make_shared<Stage>());
	objects_.push_back(std::make_shared<Player>(&camera_->dir_));

	for (auto& obj : objects_)
	{
		obj->Init();
	}

}

Game::~Game()
{

}

void Game::Init()
{
	for (auto& obj : objects_)
	{
		obj->Init();
	}
}

void Game::Update()
{
	camera_->Update();

	for (auto& obj : objects_)
	{
		obj->Update();
	}

	Physics::GetInstance().Update();

}

void Game::Draw()
{
	for (auto& obj : objects_)
	{
		obj->Draw();
	}

	if (Debug::GetInstance().GetIsDisp())
	{
		for (auto& obj : objects_)
		{
			obj->Debug();
		}

		camera_->Debug();
	}
}