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
#include"object_setter.h"
#include"collision.h"
#include"input_manager.h"
#include"brain.h"
#include"enemy_base.h"
Game::Game()
	: SceneBase()
{
	camera_ = std::make_shared<Camera>();

	objects_.push_back(std::make_shared<Stage>());
	objects_.push_back(std::make_shared<Player>(&camera_->dir_,InputManager::GetInstance().GetPlayerInput()));
	objects_.push_back(std::make_shared<EnemyBase>());
	Init();
	
}

Game::~Game()
{

}

void Game::Init()
{
	for (auto& obj : objects_)
	{
		obj->Init();
		if (auto player = std::dynamic_pointer_cast<Player>(obj))
		{
			Brain::GetInstance().CreatePlaySceneVirtualCamera(player, camera_->GetPos(), camera_->GetTargetPos());
		}
	}
}

void Game::Update()
{
	//printfDx("---‚Ü‚¢‚é[‚Õ---\n");
	for (auto& obj : objects_)
	{
		if (!obj->GetIsActive()) { continue; }
		obj->Update();
	}

	Physics::GetInstance().Update();
	ObjectSetter::GetInstance().Update();
	
	for (auto& obj : objects_)
	{
		if (!obj->GetIsActive()) { continue; }
		obj->LateUpdate();
	}

	Brain::GetInstance().Update();
	camera_->Update();

	/*
	VECTOR dir = VGet(0, 0, 0);

	if (CheckHitKey(KEY_INPUT_W)) { dir = VAdd(dir, VGet(0, 1, 0)); }
	if (CheckHitKey(KEY_INPUT_S)) { dir = VAdd(dir, VGet(0, -1, 0)); }
	if (CheckHitKey(KEY_INPUT_A)) { dir = VAdd(dir, VGet(-1, 0, 0)); }
	if (CheckHitKey(KEY_INPUT_D)) { dir = VAdd(dir, VGet(1, 0, 0)); }

	capsule_pos = VAdd(capsule_pos, dir);

	VECTOR capsule_end_pos = VAdd(capsule_pos, VGet(0, vertical, 0));
	VECTOR capsule2_end_pos = VAdd(capsule2_pos, VGet(capsule2_vertical, 0, 0));

	if (Collision::CapsuleToCapsule(capsule_pos,capsule_end_pos,capsule_r,capsule2_pos, capsule2_end_pos,capsule2_r))
	{
		printfDx("“–‚½‚Á‚Ä‚é\n");
	}
	else
	{
		printfDx("“–‚½‚Á‚Ä‚È‚¢\n");
	}
	*/
	
}

void Game::Draw()
{

	//DrawCapsule3D(capsule_pos, VAdd(capsule_pos,VGet(0,vertical,0)), capsule_r, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	//DrawCapsule3D(capsule2_pos, VAdd(capsule2_pos,VGet(capsule2_vertical,0.f,0.f)),capsule2_r, 20, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);

	
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
		Physics::GetInstance().Debug();

		camera_->Debug();
	}
	
	
}