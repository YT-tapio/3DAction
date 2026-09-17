#pragma once
#include"virtual_camera_base.h"

class IEnemyController;

class EnemyLockOnCamera : public VirtualCameraBase
{
public:

	EnemyLockOnCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos, VECTOR* main_player_head_pos,std::weak_ptr<IEnemyController> enemy_controller);

	~EnemyLockOnCamera() override;

	virtual void Awake();

	virtual void Init();

	virtual void Update();

private:

	/// <summary>
	/// 敵への視点移動
	/// </summary>
	void GoToEnemyTargetPos(std::shared_ptr<IEnemyController> enemy_controller);

	/// <summary>
	/// プレイヤーと敵の直線上に移動
	/// </summary>
	void GoToStraightLine(std::shared_ptr<IEnemyController> enemy_controller);

private:

	std::weak_ptr<IEnemyController> enemy_controller_;

	// 敵の参照
	std::function<VECTOR()> enemy_pos_;
	VECTOR* main_player_head_pos_;
};