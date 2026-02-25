#pragma once
#include"virtual_camera_base.h"

class TrackingCamera : public VirtualCameraBase
{
public:

	TrackingCamera(VECTOR* tracking_pos, VECTOR* camera_pos, VECTOR* target_pos);

	~TrackingCamera() override;

	void Init() override;

	void Update() override;

private:

	VECTOR* tracking_object_pos_;
	VECTOR tracking_obj_to_camera_dist_;
};
