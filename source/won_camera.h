#pragma once
#include"virtual_camera_base.h"
class ConditionTimer;

class WonCamera : public VirtualCameraBase
{
public:

	WonCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos, std::function<VECTOR()> enemy_center_pos, std::function<VECTOR()> enemy_dir);

	~WonCamera();

	void Init() override;

	void Update() override;

private:

	const float kPlayerToEnemyDistSize = 35.f;
	
	std::shared_ptr<ConditionTimer> timer_;
	
	VECTOR offset_;	// オフセット値
	// 注視点
	std::function<VECTOR()> enemy_center_pos_;
	// 敵の正面方向
	std::function<VECTOR()> enemy_dir_;

	VECTOR future_pos_;
};
