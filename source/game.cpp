#include<iostream>
#include<memory>
#include"DxLib.h"
#include"game.h"
#include"camera.h"
#include"object_base.h"
#include"stage.h"

Game::Game()
	: SceneBase()
{
	camera_ = std::make_shared<Camera>();

	objects_.push_back(std::make_shared<Stage>());
}

Game::~Game()
{

}

void Game::Update()
{
	camera_->Update();

	for (auto& obj : objects_)
	{
		obj->Update();
	}

}

void Game::Draw()
{
	for (auto& obj : objects_)
	{
		obj->Draw();
	}
}