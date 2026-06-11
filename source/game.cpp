#include<iostream>
#include<memory>
#include<unordered_map>
#include<functional>
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
#include"player_group.h"
#include"random.h"
#include"skydome.h"
#include"collision_mesh_obj.h"
#include"player_ui_group.h"

Game::Game()
	: SceneBase()
{
	camera_ = std::make_shared<Camera>();

	objects_.push_back(std::make_shared<EnemyBase>(VGet(10, 0, 10)));
	objects_.push_back(std::make_shared<Stage>());
	objects_.push_back(std::make_shared<SkyDome>());
	objects_.push_back(std::make_shared<CollisionMeshObject>());
	EffectManager::GetInstance().Awake();
	PlayerGroup::GetInstance().Awake(&camera_->dir_);
	Init();
}

Game::~Game()
{
	objects_.clear();
	Physics::GetInstance().End();
	PlayerGroup::GetInstance().End();
	EffectManager::GetInstance().End();
}

void Game::Init()
{
	Physics::GetInstance().Init();
	EffectManager::GetInstance().Init();
	PlayerGroup::GetInstance().Init();
	for (auto& obj : objects_)
	{
		obj->Init();
	}
	Brain::GetInstance().CreatePlaySceneVirtualCamera(camera_->GetPos(), camera_->GetTargetPos());
	camera_->Init();
}

void Game::Update()
{
	//printfDx("%d\n", GetRandom(0, 3));
	PlayerGroup::GetInstance().Update();
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

	PlayerGroup::GetInstance().LateUpdate();
	for (auto& obj : objects_)
	{
		if (!obj->GetIsActive()) { continue; }
		obj->LateUpdate();
	}

	PlayerUIGroup::GetInstance().Update();

	if (CheckHitKey(KEY_INPUT_5)) 
	{ 
		EffectManager::GetInstance().Play(EffectID::test);
	}

	if (CheckHitKey(KEY_INPUT_6))
	{
		EffectManager::GetInstance().Play(EffectID::test2);
	}

	if (CheckHitKey(KEY_INPUT_7))
	{
		EffectManager::GetInstance().Stop(EffectID::test);
	}
	
	if (CheckHitKey(KEY_INPUT_8))
	{
		EffectManager::GetInstance().RePlay(EffectID::test);
	}

	if (CheckHitKey(KEY_INPUT_9))
	{
		EffectManager::GetInstance().End(EffectID::test,EffectEndState::kMoment);
	}

	if (CheckHitKey(KEY_INPUT_0))
	{
		EffectManager::GetInstance().End(EffectID::test, EffectEndState::kTotal);
	}

	EffectManager::GetInstance().Update();
}

void Game::Draw()
{

	PlayerGroup::GetInstance().Draw();
	for (auto& obj : objects_)
	{
		obj->Draw();
	}
	// Physics::GetInstance().Debug();
	PlayerUIGroup::GetInstance().Draw();

	if (Debug::GetInstance().GetIsDisp())
	{
		PlayerGroup::GetInstance().Debug();
		for (auto& obj : objects_)
		{
			obj->Debug();
		}
		Physics::GetInstance().Debug();

		camera_->Debug();
	}
	
	EffectManager::GetInstance().Draw();
}

const std::string Game::GetName() const
{
	return "game";
}