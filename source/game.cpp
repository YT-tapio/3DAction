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
#include"boss_base.h"
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
#include"scene_manager.h"
#include"input_base.h"
#include"sound_manager.h"
#include"game_start_timer.h"
#include"fade.h"
#include"won_ui.h"
#include"lose_ui.h"
#include"game_to_next_scene.h"
#include"shadow_circle_controller.h"
#include"damage_ui_group_interface.h"

Game::Game()
	: SceneBase()
{
	AttackRangeGroup::GetInstance().Awake();
	//StatModifires::GetInstance().Awake();
	damage_ui_group_ = std::make_shared<DamageUIGroup>();
	damage_ui_group_->Awake();
	//StatModifireUIData::GetInstance().Load();
	enemy_ui_group_ = std::make_shared<EnemyUIGroup>();
	shadow_circle_controller_ = std::make_shared<ShadowCircleController>();
	game_start_ = FALSE;
	camera_ = std::make_shared<Camera>();
	shadow_map_ = std::make_shared<ShadowMap>();
	std::shared_ptr<EnemyBase> enemy = std::make_shared<BossBase>(VGet(0, 0, 0), &game_start_,shadow_circle_controller_,enemy_ui_group_, damage_ui_group_);
	get_enemy_pos_ = [enemy]()
		{
			return enemy->GetCenterPos();
		}; 
	
	get_enemy_dir_ = [enemy]()
		{
			return enemy->GetFrontDir();
		};
	won_ui_ = std::make_shared<WonUI>();
	lose_ui_ = std::make_shared<LoseUI>();
	game_to_next_scene_ = std::make_shared<GameToNextScene>();
	enemy->AddObserver(won_ui_.get());
	enemy->AddObserver(game_to_next_scene_.get());

	player_ui_group_ = std::make_shared<PlayerUIGroup>();
	player_skill_ui_group_ = std::make_shared<PlayerSkillUIGroup>();

	//PlayerGroup::GetInstance().Awake(&camera_->dir_, player_ui_group_, enemy,shadow_circle_controller_, damage_ui_group_);
	PlayerGroup::GetInstance().Awake(&camera_->dir_, player_ui_group_, enemy, shadow_circle_controller_, damage_ui_group_);
	objects_.push_back(enemy);

	objects_.push_back(std::make_shared<Stage>());
	
	no_shadow_objects_.push_back(std::make_shared<SkyDome>());
	game_start_timer_ = std::make_shared<GameStartTimer>(&game_start_);
	
	PlayerGroup::GetInstance().AddPlayerObserver(won_ui_.get());
	PlayerGroup::GetInstance().AddPlayerObserver(lose_ui_.get());
	PlayerGroup::GetInstance().AddPlayerObserver(game_to_next_scene_.get());
	//Init();
	is_finished_fade_ = FALSE;
	SoundManager::GetInstance().Play2DSound("game_bgm");
	Fade::GetInstance().StartFadeOut(3.f);
	
}

Game::~Game()
{
	ObjectSetter::GetInstance().DeleteResource();
	PlayerGroup::GetInstance().End();
	objects_.clear();
	no_shadow_objects_.clear();
	Physics::GetInstance().End();
	//EffectManager::GetInstance().End();
	AttackRangeGroup::GetInstance().End();
	//StatModifires::GetInstance().End();
	//StatModifireUIData::GetInstance().End();
	SoundManager::GetInstance().AllStop();
}

void Game::Init()
{
	AttackRangeGroup::GetInstance().Init();
	Physics::GetInstance().Init();
	EffectManager::GetInstance().Init();
	PlayerGroup::GetInstance().Init(player_skill_ui_group_);
	won_ui_->Init();
	for (auto& obj : objects_)
	{
		obj->Init();
	}

	for (auto obj : no_shadow_objects_)
	{
		obj->Init();
	}
	player_ui_group_->Init();
	Brain::GetInstance().CreatePlaySceneVirtualCamera(camera_->GetPos(), camera_->GetTargetPos(), get_enemy_pos_, get_enemy_dir_);
	damage_ui_group_->Init();
	//damage_ui_group_->Init(head_pos, final_damage);
	camera_->Init();
	shadow_map_->Init();
	game_start_timer_->Init();
}

void Game::Update()
{
	if (Fade::GetInstance().IsFinished())
	{
		is_finished_fade_ = TRUE;
	}

	if (is_finished_fade_)
	{
		game_start_timer_->Update();
	}

	if (game_to_next_scene_->Update()) { return; }

	if (InputManager::GetInstance().GetMainPlayerInput()->GoResult())
	{
		if (SceneManager::GetInstance().LoadScene("title")) { return; }
	}

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
	won_ui_->Update();
	lose_ui_->Update();
	enemy_ui_group_->Update();
	damage_ui_group_->Update();
	EffectManager::GetInstance().Update();
	AttackRangeGroup::GetInstance().Update();
	shadow_circle_controller_->Update();
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
		shadow_circle_controller_->Draw();
		Physics::GetInstance().Debug();
	}
	else
	{
		// 影

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
	won_ui_->Draw();
	lose_ui_->Draw();
	game_start_timer_->Draw();
	enemy_ui_group_->Draw();
	damage_ui_group_->Draw();

	if (Debug::GetInstance().GetIsDisp())
	{
		camera_->Debug();
		PlayerGroup::GetInstance().Debug();
		for (auto& obj : objects_)
		{
			obj->Debug();
		}
		
	}
	
	EffectManager::GetInstance().Draw();
	// DrawString(1200, 860, "十字 右ボタン、Enterを押してリザルトへ", GetColor(0, 0, 0));
}

const std::string Game::GetName() const
{
	return "game";
}