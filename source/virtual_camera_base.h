#pragma once
#include<memory>

class VariableTimer;

class VirtualCameraBase
{
public:

	VirtualCameraBase(VECTOR* pos, VECTOR* target_pos);

	virtual ~VirtualCameraBase();

	virtual void Awake();

	virtual void Init();

	/// @brief 独自のupdateを行い戻り値を返す
	/// @return 移動量
	virtual void Update();

	void Active();

	void NotActive();

	VECTOR GetVelocity();

	VECTOR GetTargetVelocity();

protected:

	/// <summary>
	/// center_posからyawとpitchから座標を定める
	/// </summary>
	VECTOR GetPosFromYawPitch(const VECTOR& center_pos, const float& target_to_camera_dist_size, const float& yaw,const float& pitch);

protected:

	VECTOR* main_camera_pos_;							// 自分の位置
	VECTOR* main_camera_target_pos_;				// 見る位置
	VECTOR vel_;						// 自分の移動量
	VECTOR target_vel_;	// ターゲットの移動量

private:

	bool is_active_;

	int priority_;
	
	float shake_power_;
};