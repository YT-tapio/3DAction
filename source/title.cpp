#include<string>
#include<memory>
#include"DxLib.h"
#include"title.h"
#include"scene_manager.h"
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

Title::Title()
	: SceneBase()
{
	//title_logo_handle_		= LoadGraph("data/ui/title/title_logo.png");
	//player_handle_			= MV1LoadModel("data/model/player/attacker/Lola_B_Styperek.mv1");
	//enemy_handle_			= MV1LoadModel("data/model/enemy/zako/Demon_T_Wiezzorek.mv1");
	//stage_handle_			= MV1LoadModel("data/model/stage/field.mv1");
	//sky_dome_handle_		= MV1LoadModel("data/model/skydome/SkyDome.mv1");

	title_logo_handle_ = -1;
	player_handle_ = -1;
	enemy_handle_ = -1;
	sky_dome_handle_ = -1;

	if (player_handle_ == -1)
	{
		printfDx("モデル読み込みエラー\n");
	}
	if (enemy_handle_ == -1)
	{
		printfDx("モデル読み込みエラー\n");
	}
	if (sky_dome_handle_ == -1)
	{
		printfDx("モデル読み込みエラー\n");
	}

	float near_feat = 0.1f;
	float far_feat = 500.f;

	float fov = RadianAssistant::TheNumRadian(75.f);
	VECTOR pos = VGet(0, 0, 0);
	VECTOR target_pos = VGet(0, 0, 10);
	SetCameraNearFar(near_feat, far_feat);
	SetupCamera_Perspective(fov);
	SetCameraPositionAndTarget_UpVecY(pos, target_pos);

	//MV1SetScale(stage_handle_, VectorAssistant::VGetSame(0.3f));
	//MV1SetPosition(stage_handle_, VGet(0,0,0));

	MV1SetScale(sky_dome_handle_, VectorAssistant::VGetSame(200.f));
	MV1SetPosition(sky_dome_handle_, VGet(0, 0, 0));

	MV1SetScale(player_handle_, VectorAssistant::VGetSame(0.05f));
	MV1SetPosition(player_handle_, VGet(2.1f, -8.5f, 1.7f));
	MV1SetRotationXYZ(player_handle_, VGet(0.f, RadianAssistant::TheNumRadian(90), 0.f));

	MV1SetScale(enemy_handle_, VectorAssistant::VGetSame(0.05f));
	MV1SetPosition(enemy_handle_, VGet(-2.4f, -8.5f, 2.3f));
	MV1SetRotationXYZ(enemy_handle_, VGet(0.f, RadianAssistant::TheNumRadian(-90), 0.f));
	/*
	int player_anim_handle = MV1LoadModel("data/model/player/animation/Idle.mv1");
	int enemy_anim_handle = MV1LoadModel("data/model/enemy/zako/animation/Idle.mv1");
	*/
	
	int player_anim_handle = -1;
	int enemy_anim_handle = -1;
	/*
	//アニメーションのアタッチ
	MV1AttachAnim(player_handle_, 0,player_anim_handle, FALSE);
	MV1AttachAnim(enemy_handle_, 0, enemy_anim_handle, FALSE);
	*/
	
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
	/*
	MV1DeleteModel(player_anim_handle);
	MV1DeleteModel(enemy_anim_handle);
	*/
	
}

Title::~Title()
{
	SoundManager::GetInstance().Stop("title_bgm");

	DeleteGraph(title_logo_handle_);
	MV1DeleteModel(player_handle_);
	MV1DeleteModel(enemy_handle_);
	//MV1DeleteModel(stage_handle_);
	MV1DeleteModel(sky_dome_handle_);
}

void Title::Init()
{

}

void Title::Update()
{
	start_button_->Update();
	offset_timer_->Update();
	
	if (offset_timer_->GetIsEnd())
	{
		SceneManager::GetInstance().LoadScene("game");
	}
}

void Title::Draw()
{
	MV1DrawModel(player_handle_);
	MV1DrawModel(enemy_handle_);
	MV1DrawModel(sky_dome_handle_);
	Draw2D::RotaGraph(VectorAssistant::VGet2D(static_cast<float>(kScreenWidth * 0.5f), 750.f), 0.7f, 0.f, title_logo_handle_, TRUE);
	
	DrawString(700, 400, "Aボタン、スペースを押してゲームスタート", GetColor(255, 0, 0));
	start_button_->Draw();
}

const std::string Title::GetName() const
{
	return "title";
}
