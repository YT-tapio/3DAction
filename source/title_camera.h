#pragma once
#include"virtual_camera_base.h"

class TitleCamera : public VirtualCameraBase
{
public:

	TitleCamera(VECTOR* pos, VECTOR* target_pos);

	~TitleCamera() override;

	void Awake() override;

	void Init() override;

	void Update() override;

private:

	void FirstUpdate();

	void SecondUpdate();

	void ThirdUpdate();

private:

	enum class Phase
	{
		first,
		second,
		third
	};


	Phase phase_;

};