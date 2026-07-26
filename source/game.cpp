#include<iostream>
#include<memory>
#include<unordered_map>
#include<functional>
#include<vector>
#include<string>
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
#include"enemy_ui_group.h"
#include"attack_range_group.h"
#include"shadow_map.h"
#include"stat_modifire.h"
#include"stat_modifires.h"
#include"damage_ui_group.h"
#include"stat_modifire_ui_data.h"
#include"player_skill_ui_group.h"

Game::Game()
	: SceneBase()
{
	AttackRangeGroup::GetInstance().Awake();
	StatModifires::GetInstance().Awake();
	camera_ = std::make_shared<Camera>();
	shadow_map_ = std::make_shared<ShadowMap>();
	objects_.push_back(std::make_shared<EnemyBase>(VGet(10, 0, 10)));
	objects_.push_back(std::make_shared<Stage>());
	objects_.push_back(std::make_shared<CollisionMeshObject>());

	player_ui_group_ = std::make_shared<PlayerUIGroup>();
	player_skill_ui_group_ = std::make_shared<PlayerSkillUIGroup>();
	no_shadow_objects_.push_back(std::make_shared<SkyDome>());
	
	EffectManager::GetInstance().Awake();
	PlayerGroup::GetInstance().Awake(&camera_->dir_,player_ui_group_);
	DamageUIGroup::GetInstance().Awake();
	StatModifireUIData::GetInstance().Load();
	Init();
}

Game::~Game()
{
	objects_.clear();
	no_shadow_objects_.clear();
	Physics::GetInstance().End();
	PlayerGroup::GetInstance().End();
	EffectManager::GetInstance().End();
	DamageUIGroup::GetInstance().End();
	StatModifireUIData::GetInstance().End();
}

void Game::Init()
{
	AttackRangeGroup::GetInstance().Init();
	Physics::GetInstance().Init();
	EffectManager::GetInstance().Init();
	PlayerGroup::GetInstance().Init(player_skill_ui_group_);
	for (auto& obj : objects_)
	{
		obj->Init();
	}

	for (auto obj : no_shadow_objects_)
	{
		obj->Init();
	}
	player_ui_group_->Init();

	Brain::GetInstance().CreatePlaySceneVirtualCamera(camera_->GetPos(), camera_->GetTargetPos());
	DamageUIGroup::GetInstance().Init();
	camera_->Init();
	shadow_map_->Init();
}

void Game::Update()
{
	PlayerGroup::GetInstance().Update();
	for (auto& obj : objects_)
	{
		if (!obj->GetIsActive()) { continue; }
		obj->Update();
	}
	for (auto obj : no_shadow_objects_)
	{
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

	for (auto obj : no_shadow_objects_)
	{
		obj->LateUpdate();
	}
	player_ui_group_->Update();
	player_skill_ui_group_->Update();
	EnemyUIGroup::GetInstance().Update();
	DamageUIGroup::GetInstance().Update();
	EffectManager::GetInstance().Update();
	AttackRangeGroup::GetInstance().Update();
}

void Game::Draw()
{
	if (TRUE)
	{
		PlayerGroup::GetInstance().Draw();
		for (const auto& obj : objects_)
		{
			obj->Draw();
		}
	}
	else
	{
		// ‰e

		shadow_map_->UpDrawShadowObject();
		PlayerGroup::GetInstance().Draw();
		for (const auto& obj : objects_)
		{
			obj->Draw();
		}
		// DrawTriangle3D(VGet(5.f, -3.f, 5.f), VGet(50.f, -15.f, 5.f), VGet(5.f, -3.f, 50.f), GetColor(255, 255, 255), TRUE);
		shadow_map_->DownDrawShadowObject();

		shadow_map_->UpDrawnShadowObject();
		PlayerGroup::GetInstance().Draw();
		for (const auto& obj : objects_)
		{
			obj->Draw();
		}
		// DrawTriangle3D(VGet(5.f, -3.f, 5.f), VGet(50.f, -15.f, 5.f), VGet(5.f, -3.f, 50.f), GetColor(255, 255, 255), TRUE);
		shadow_map_->DownDrawnShadowObject();
	}
	
	AttackRangeGroup::GetInstance().Draw();

	// DrawSphere3D(VGet(-500.0f, -100.0f, -500.0f), 10, 10, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
	// DrawSphere3D(VGet(500.0f, 50.0f, 500.0f), 10, 10, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);

	for (auto obj : no_shadow_objects_)
	{
		obj->Draw();
	}

	// Physics::GetInstance().Debug();
	player_ui_group_->Draw();
	player_skill_ui_group_->Draw();
	EnemyUIGroup::GetInstance().Draw();
	DamageUIGroup::GetInstance().Draw();
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