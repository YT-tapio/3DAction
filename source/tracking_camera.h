#pragma once
#include"virtual_camera_base.h"

class TrackingCamera : public VirtualCameraBase
{
public:

	TrackingCamera(VECTOR* pos);

	~TrackingCamera() override;

	void Init(const VECTOR& camera_pos, const VECTOR& target_pos) override;

	void Update() override;

private:

	VECTOR* tracking_object_pos_;
	
};
