#pragma once
#include"virtual_camera_base.h"

class EnemyLockOnCamera : public VirtualCameraBase
{
public:

	EnemyLockOnCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos, VECTOR* main_player_head_pos, std::function<VECTOR()> enemy_head_pos);

	~EnemyLockOnCamera();

	virtual void Awake();

	virtual void Init();

	virtual void Update();

private:

	/// <summary>
	/// 敵への視点移動
	/// </summary>
	void GoToEnemyTargetPos();

	/// <summary>
	/// プレイヤーと敵の直線上に移動
	/// </summary>
	void GoToStraightLine();

private:

	// 敵の参照
	std::function<VECTOR()> enemy_pos_;
	VECTOR* main_player_head_pos_;
};