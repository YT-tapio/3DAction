#pragma once
#include"virtual_camera_base.h"

class InputBase;

class SphereCamera : public VirtualCameraBase
{
public:

	SphereCamera(VECTOR* center_pos,VECTOR* pos, VECTOR* target_pos);

	~SphereCamera()override;

	void Awake() override;

	void Init() override;

	void Update() override;

private:

	void MakeYawPitch();

	static constexpr float kYawRadMax = 85.f;
	static constexpr float kYawRadMin = 50.f;

	std::shared_ptr<const InputBase> input_;

	VECTOR* center_pos_;
	VECTOR rotation_;

	VECTOR future_pos_;

	float target_to_camera_dist_size_;
	float yaw_;		// yé≤
	float pitch_;	// xé≤
};