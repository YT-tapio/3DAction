#pragma once

class VirtualCameraBase
{
public:

	VirtualCameraBase(VECTOR* pos, VECTOR* target_pos);

	virtual ~VirtualCameraBase();

	virtual void Init();

	/// @brief 独自のupdateを行い戻り値を返す
	/// @return 移動量
	virtual void Update();

	void Active();

	void NotActive();

	VECTOR GetVelocity();

	VECTOR GetTargetVelocity();

protected:

	VECTOR* pos_;							// 自分の位置
	VECTOR* target_pos_;				// 見る位置
	VECTOR vel_;						// 自分の移動量
	VECTOR target_vel_;	// ターゲットの移動量

private:
	bool is_active_;
	int priority_;
};