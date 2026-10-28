#pragma once
#include"virtual_camera_base.h"

class TitleFirstCamera : public VirtualCameraBase
{
public:

	TitleFirstCamera(VECTOR* pos, VECTOR* target_pos, std::function<VECTOR()> get_head_pos);

	~TitleFirstCamera() override;

	void Awake() override;

	void Init() override;

	void Update() override;

private:

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