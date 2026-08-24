#include<functional>
#include"DxLib.h"
#include"enemy_lock_on_camera.h"
#include"FPS.h"
#include"lerp.h"
#include"vector_assistant.h"

EnemyLockOnCamera::EnemyLockOnCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos, VECTOR* main_player_head_pos, std::function<VECTOR()> enemy_head_pos)
	: VirtualCameraBase(main_camera_pos,main_camera_target_pos)
	, enemy_pos_(enemy_head_pos)
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
	// 敵の場所へ移動
	GoToEnemyTargetPos();
	// プレイヤーと敵の直線上のポジションへ移動
	GoToStraightLine();
}

void EnemyLockOnCamera::GoToEnemyTargetPos()
{
	// 敵の注視点に行くまでのスピード
	float target_pos_move_speed = 0.1f;

	auto main_camera_target_pos = *main_camera_target_pos_;
	auto future_target_pos = Lerp::DampV(main_camera_target_pos, enemy_pos_(), target_pos_move_speed * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS());
	// 注視点までの移動量
	target_vel_ = VSub(future_target_pos, main_camera_target_pos);
}

void EnemyLockOnCamera::GoToStraightLine()
{
	float pos_move_speed = 0.2f;

	auto main_camera_pos = *main_camera_pos_;
	auto player_to_enemy_dir = VectorAssistant::VGetFlat(VectorAssistant::VGetDir(*main_player_head_pos_,enemy_pos_()));
	auto player_to_enemy_line_pos = VScale(VectorAssistant::VGetReverce(player_to_enemy_dir), 10.f);
	player_to_enemy_line_pos = VAdd(player_to_enemy_line_pos, *main_player_head_pos_);
	VECTOR offset = VGet(0.f, 0.f, 0.f);
	auto future_pos = Lerp::DampV(main_camera_pos, VAdd(player_to_enemy_line_pos, offset), pos_move_speed * FPS::GetInstance().GetDeltaTime() * FPS::GetInstance().GetTargetFPS());
	vel_ = VSub(future_pos, main_camera_pos);
}