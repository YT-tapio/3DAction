#include<functional>
#include"DxLib.h"
#include"enemy_lock_on_camera.h"
#include"FPS.h"
#include"lerp.h"
#include"vector_assistant.h"
#include"enemy_controller_interface.h"

EnemyLockOnCamera::EnemyLockOnCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos, VECTOR* main_player_head_pos, std::weak_ptr<IEnemyController> enemy_controller)
	: VirtualCameraBase(main_camera_pos,main_camera_target_pos)
	, enemy_controller_(enemy_controller)
	, main_player_head_pos_(main_player_head_pos)
{

}

EnemyLockOnCamera::~EnemyLockOnCamera()
{

}

void EnemyLockOnCamera::Awake()
{

}

void EnemyLockOnCamera::Init()
{

}

void EnemyLockOnCamera::Update()
{
	if (auto enemy_controller = enemy_controller_.lock())
	{
		// 敵の場所へ移動
		GoToEnemyTargetPos(enemy_controller);
		// プレイヤーと敵の直線上のポジションへ移動
		GoToStraightLine(enemy_controller);
	}
	
}

void EnemyLockOnCamera::GoToEnemyTargetPos(std::shared_ptr<IEnemyController> enemy_controller)
{
	// 敵の注視点に行くまでのスピード
	float target_pos_move_speed = 0.1f;

	auto main_camera_target_pos = *main_camera_target_pos_;
	auto future_target_pos = Lerp::DampV(main_camera_target_pos, enemy_controller->GetBossCenterPos(), target_pos_move_speed * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS());
	// 注視点までの移動量
	target_vel_ = VSub(future_target_pos, main_camera_target_pos);
}

void EnemyLockOnCamera::GoToStraightLine(std::shared_ptr<IEnemyController> enemy_controller)
{
	float pos_move_speed = 0.2f;

	auto main_camera_pos = *main_camera_pos_;
	auto player_to_enemy_dir = VectorAssistant::VGetFlat(VectorAssistant::VGetDir(*main_player_head_pos_,enemy_controller->GetBossCenterPos()));
	auto player_to_enemy_line_pos = VScale(VectorAssistant::VGetReverce(player_to_enemy_dir), 10.f);
	player_to_enemy_line_pos = VAdd(player_to_enemy_line_pos, *main_player_head_pos_);
	VECTOR offset = VGet(0.f, 0.f, 0.f);
	auto future_pos = Lerp::DampV(main_camera_pos, VAdd(player_to_enemy_line_pos, offset), pos_move_speed * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS());
	vel_ = VSub(future_pos, main_camera_pos);
}