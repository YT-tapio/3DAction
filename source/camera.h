#pragma once

class Camera
{
public:

	Camera();

	~Camera();

	void Update();

private:

	VECTOR pos_;				// 自身の座標
	VECTOR target_pos_;		// 注視点の座標
	VECTOR dir_;					// カメラの正面
	
	float near_;
	float far_;

	float fov_;

	/// <summary>
	/// カメラのpos,near,farなどのセッティングを行う
	/// </summary>
	void Setting();

};