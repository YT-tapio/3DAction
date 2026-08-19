#pragma once
#include"virtual_camera_base.h"

class LoseCamera :public VirtualCameraBase
{
public:

	LoseCamera(VECTOR* main_camera_pos, VECTOR* main_camera_target_pos);

	~LoseCamera() override;

	void Awake() override;

	void Init() override;

	void Update() override;

private:

	

};