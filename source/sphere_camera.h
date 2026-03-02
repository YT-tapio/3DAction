#pragma once
#include"virtual_camera_base.h"

class InputBase;

class SphereCamera : public VirtualCameraBase
{
public:

	SphereCamera(VECTOR* center_pos,VECTOR* pos, VECTOR* target_pos);

	~SphereCamera()override;

	void Init() override;

	void Update() override;


private:

	std::shared_ptr<const InputBase> input_;

	VECTOR* center_pos_;
	VECTOR rotation_;
};