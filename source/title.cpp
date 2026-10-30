#include<string>
#include<memory>
#include"DxLib.h"
#include"title.h"
#include"scene_manager.h"
#include<unordered_map>
#include"physics.h"
#include"input_manager.h"
#include"input_base.h"
#include"object_3d.h"
#include"skydome.h"
#include"object_setter.h"
#include"radian_assistant.h"
#include"vector_assistant.h"
#include<functional>
#include"draw_2D.h"
#include"screen_size.h"
#include"fade.h"
#include"sound_manager.h"
#include"button_ui.h"
#include"condition_timer.h"
#include"variable_timer.h"

#include"model_repository.h"
#include"brain.h"
#include"camera.h"

#include"debug.h"
#include"title_player_controller.h"
#include"title_enemy_controller.h"
#include"logo_controller.h"
#include"start_guide.h"

Title::Title()
	: SceneBase()
{
	camera_ = std::make_shared<Camera>(VGet(-5.f,0.f,0.f), VGet(0.f, 0.f, 10.f),FALSE);
	title_logo_handle_		= LoadGraph("data/ui/title/title_logo.png");
	stage_handle_			= MV1LoadModel("data/model/stage/field.mv1");
	sky_dome_handle_		= MV1LoadModel("data/model/skydome/SkyDome.mv1");

	if (sky_dome_handle_ == -1)
	{
		printfDx("ÉÇÉfÉãì«Ç›çûÇ›ÉGÉâÅ[\n");
	}
	
	MV1SetScale(stage_handle_, VectorAssistant::VGetSame(0.3f));
	auto stage_pos = VGet(0.f, -12.f, 0.f);
	MV1SetPosition(stage_handle_, stage_pos);
	
	MV1SetScale(sky_dome_handle_, VectorAssistant::VGetSame(200.f));
	MV1SetPosition(sky_dome_handle_, VGet(0, 0, 0));

	offset_timer_ = std::make_shared<VariableTimer>(2.f);
	offset_timer_->Stop();
	SoundManager::GetInstance().Play2DSound("title_bgm");
	Fade::GetInstance().StartFadeOut(1.f);
	std::function<void()> start_function = [this]()
		{
			SoundManager::GetInstance().Play2DSound("go_game");
			Fade::GetInstance().StartFadeIn(1.f, FadeColorType::kBlack);
			offset_timer_->ReStart();
		};

	start_button_ = std::make_shared<ButtonUI>(ConfigName::play, VectorAssistant::VGet2D(700.f, 650.f), 0.1f, start_function);
	
	player_controller_ = std::make_shared<TitlePlayerController>();
	player_controller_->Awake();
	enemy_controller_ = std::make_shared<TitleEnemyController>();
	enemy_controller_->Awake();
	logo_controller_ = std::make_shared<LogoController>();
	logo_controller_->Awake();
	start_ui_ = std::make_shared<StartGuide>();
	start_ui_->Awake();
	Brain::GetInstance().CreateTitleSceneVirtualCamera(camera_->GetPos(),camera_->GetTargetPos(),player_controller_);
	is_stop_ = FALSE;
}

Title::~Title()
{
	Physics::GetInstance().End();
	SoundManager::GetInstance().Stop("title_bgm");
	Brain::GetInstance().DeleteVirtualCamera();
	DeleteGraph(title_logo_handle_);
	MV1DeleteModel(stage_handle_);
	MV1DeleteModel(sky_dome_handle_);
}

void Title::Init()
{
	Physics::GetInstance().Init();
	player_controller_->Init();
	enemy_controller_->Init();
}

void Title::Update()
{
	if (CheckHitKey(KEY_INPUT_8))
	{
		ReStart();
		is_stop_ = FALSE;
	}

	if (CheckHitKey(KEY_INPUT_9))
	{
		Brain::GetInstance().ChangeCamera("title_camera");
		is_stop_ = FALSE;
	}

	if (CheckHitKey(KEY_INPUT_0))
	{
		Brain::GetInstance().ChangeCamera("debug_camera");
		is_stop_ = TRUE;
	}
	
	Brain::GetInstance().Update();
	camera_->Update();
	start_button_->Update();
	offset_timer_->Update();
	start_ui_->Update();
	if (!is_stop_)
	{
		player_controller_->Update();
		enemy_controller_->Update();
		logo_controller_->Update();

		Physics::GetInstance().Update();

		player_controller_->LateUpdate();
		enemy_controller_->LateUpdate();
	}
	
	if (offset_timer_->GetIsEnd())
	{
		SceneManager::GetInstance().LoadScene("game");
	}
}

void Title::Draw()
{
	player_controller_->Draw();
	enemy_controller_->Draw();
	MV1DrawModel(enemy_handle_);
	SetUseLighting(FALSE);
	MV1DrawModel(stage_handle_);
	MV1DrawModel(sky_dome_handle_);
	SetUseLighting(TRUE);
	
	logo_controller_->Draw();
	start_ui_->Draw();
	//Draw2D::RotaGraph(VectorAssistant::VGet2D(static_cast<float>(kScreenWidth * 0.5f), 750.f), 0.7f, 0.f, title_logo_handle_, TRUE);
	
	if (Debug::GetInstance().GetIsDisp())
	{
		camera_->Debug();
		player_controller_->Debug();
		enemy_controller_->Debug();
	}

}

const std::string Title::GetName() const
{
	return "title";
}

void Title::ReStart()
{
	player_controller_->Init();
	enemy_controller_->Init();
}
