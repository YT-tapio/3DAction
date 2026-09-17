#pragma once
#include"virtual_camera_base.h"

class ConditionTimer;
class PlayerGroup;
class IEnemyController;

class WonCamera : public VirtualCameraBase
{
public:

	WonCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos, std::shared_ptr<IEnemyController>enemy_controller, std::shared_ptr<PlayerGroup> player_group);

	~WonCamera();

	void Init() override;

	void Update() override;

private:

	const float kCameraToEnemyDistSize = 40.f;
	const float kCameraToPlayerDistSize = 15.f;
	const float kOffsetDist = 10.f;
	
	std::shared_ptr<IEnemyController> enemy_controller_;
	std::shared_ptr<ConditionTimer> timer_;

	VECTOR enemy_target_offset_;	// 敵を見るときのオフセット値
	VECTOR player_target_offset_;	// プレイヤーを見るときのオフセット値
	

	VECTOR* player_cneter_pos_;
	VECTOR* player_dir_;
	VECTOR future_pos_;
	VECTOR future_target_pos_;
};
