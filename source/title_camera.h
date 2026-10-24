#pragma once
#include"virtual_camera_base.h"

class TitleCamera : public VirtualCameraBase
{
public:

	TitleCamera(VECTOR* pos, VECTOR* target_pos, std::function<VECTOR()> get_head_pos);

	~TitleCamera() override;

	void Awake() override;

	void Init() override;

	void Update() override;

private:

	void FirstPhaseUpdate();

	void SecondPhaseUpdate();

	void ThirdPhaseUpdate();

private:

	enum class Phase
	{
		first,
		second,
		third
	};

	Phase phase_;

	std::function<VECTOR()> get_head_pos_; // プレイヤーモデルの頭部座標
};