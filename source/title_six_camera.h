#pragma once
#include"virtual_camera_base.h"

class ConditionTimer;

class TitleSixCamera : public VirtualCameraBase
{
public:

	TitleSixCamera(VECTOR* main_camera_pos,VECTOR* main_camera_target_pos);

	~TitleSixCamera() override;

	void Awake() override;

	void Init() override;

	void Update() override;

private:

	void FirstPhaseUpdate();

	void SecondPhaseUpdate();

private:

	enum class Phase
	{
		kFirst,
		kSecond
	};

	const VECTOR kInitPos = VGet(-79.5f, -2.55f, -29.f);
	const VECTOR kInitTargetPos = VGet(-12.7f, -0.2f, -27.8f);
	const VECTOR kLastPos = VGet(-36.f, -1.9f, -24.4f);


	std::shared_ptr<ConditionTimer> timer_;

	Phase phase_;

};