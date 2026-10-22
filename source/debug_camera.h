#pragma once
#include"virtual_camera_base.h"

class InputBase;

class DebugCamera : public VirtualCameraBase
{
public:

	DebugCamera(VECTOR* pos, VECTOR* target_pos);

	~DebugCamera() override;

	void Awake() override;

	void Init() override;

	void Update() override;

private:

	void ResetVel();

	//’‹“_‚ğ“®‚©‚·
	void MoveTargetPos();

	// ƒJƒƒ‰‚ÌˆÚ“®
	void MoveCamera(const VECTOR& dir);

private:

	const float kYawRadMin = 0.f;
	const float kYawRadMax = 80.f;

	std::shared_ptr<const InputBase> input_;

	VECTOR future_pos_;

	float pitch_;
	float yaw_;

	float target_to_camera_dist_size_;

};