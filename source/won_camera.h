#pragma once
#include"virtual_camera_base.h"
class ConditionTimer;

class WonCamera : public VirtualCameraBase
{
public:

	WonCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos, std::function<VECTOR()> enemy_center_pos, 
		std::function<VECTOR()> enemy_dir);

	~WonCamera();

	void Init() override;

	void Update() override;

private:

	const float kCameraToEnemyDistSize = 40.f;
	const float kCameraToPlayerDistSize = 16.f;
	const float kOffsetDist = 5.f;
	std::shared_ptr<ConditionTimer> timer_;
	
	VECTOR enemy_target_offset_;	// 敵を見るときのオフセット値
	VECTOR player_target_offset_;	// プレイヤーを見るときのオフセット値
	// 注視点
	std::function<VECTOR()> enemy_center_pos_;
	// 敵の正面方向
	std::function<VECTOR()> enemy_dir_;
	

	VECTOR* player_cneter_pos_;
	VECTOR* player_dir_;
	VECTOR future_pos_;
	VECTOR future_target_pos_;
};
