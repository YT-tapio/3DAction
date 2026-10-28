#pragma once
#include"virtual_camera_base.h"

class TitleSecondCamera : public VirtualCameraBase
{
public:

	TitleSecondCamera(VECTOR* pos, VECTOR* target_pos);

	~TitleSecondCamera() override;

	void Awake() override;

	void Init() override;

	void Update() override;

private:

	const VECTOR kMyPos = VGet(-7.2f, -6.8f, 5.9f);
	const VECTOR kMyTargetPos = VGet(-30.f, -4.48f, 4.2f);
};