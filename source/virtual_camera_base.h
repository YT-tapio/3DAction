#pragma once

class VirtualCameraBase
{
public:

	VirtualCameraBase();

	virtual ~VirtualCameraBase();

	virtual void Init(const VECTOR& pos, const VECTOR& target_pos);

	/// @brief 独自のupdateを行い戻り値を返す
	/// @return 移動量
	virtual VECTOR Update();

protected:

	VECTOR pos_;		// 自分の位置
	VECTOR target_pos_;	// 見る位置
	VECTOR vel_;		// 自分の移動量
	VECTOR target_vel_;	// ターゲットの移動量

private:

};