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
#include"effect_base.h"
#include"effect_manager.h"
#include"effect_id.h"
#include"effect_end_state.h"

Game::Game()
	: SceneBase()
{
	camera_ = std::make_shared<Camera>();

	objects_.push_back(std::make_shared<Stage>());
	objects_.push_back(std::make_shared<Player>(&camera_->dir_, InputManager::GetInstance().GetAIInput(),"attacker"));
	objects_.push_back(std::make_shared<Player>(&camera_->dir_, InputManager::GetInstance().GetAIInput2(),"healer"));
	objects_.push_back(std::make_shared<Player>(&camera_->dir_, InputManager::GetInstance().GetPlayerInput(), "defender"));
	objects_.push_back(std::make_shared<EnemyBase>(VGet(10,0,2)));
	objects_.push_back(std::make_shared<EnemyBase>(VGet(10, 0, 10)));
	objects_.push_back(std::make_shared<EnemyBase>(VGet(-10, 0, 10)));
	objects_.push_back(std::make_shared<EnemyBase>(VGet(-10, 0, -10)));
	EffectManager::GetInstance().Awake();
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
	EffectManager::GetInstance().Init();
	camera_->Init();
}

void Game::Update()
{

	//printfDx("---‚Ü‚¢‚é[‚Õ---\n");
	for (auto& obj : objects_)
	{
		if (!obj->GetIsActive()) { continue; }
		obj->Update();
	}

	Brain::GetInstance().Update();
	camera_->Update();

	Physics::GetInstance().Update();
	ObjectSetter::GetInstance().Update();

	for (auto& obj : objects_)
	{
		if (!obj->GetIsActive()) { continue; }
		obj->LateUpdate();
	}
	
	
	if (CheckHitKey(KEY_INPUT_0)) 
	{ 
		EffectManager::GetInstance().Play(EffectID::test);
	}

	if (CheckHitKey(KEY_INPUT_1))
	{
		EffectManager::GetInstance().Play(EffectID::test2);
	}

	if (CheckHitKey(KEY_INPUT_2))
	{
		EffectManager::GetInstance().Stop(EffectID::test);
	}
	
	if (CheckHitKey(KEY_INPUT_3))
	{
		EffectManager::GetInstance().RePlay(EffectID::test);
	}

	if (CheckHitKey(KEY_INPUT_4))
	{
		EffectManager::GetInstance().End(EffectID::test,EffectEndState::kMoment);
	}

	if (CheckHitKey(KEY_INPUT_5))
	{
		EffectManager::GetInstance().End(EffectID::test, EffectEndState::kTotal);
	}

	EffectManager::GetInstance().Update();
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
	EffectManager::GetInstance().Draw();
}