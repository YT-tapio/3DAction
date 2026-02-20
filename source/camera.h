#pragma once

class Camera
{
public:

	Camera();

	~Camera();

	void Update();

	void Debug();

	/// <summary>
	/// カメラのpos,near,farなどのセッティングを行う
	/// </summary>
	void Setting();

	VECTOR dir_;// カメラの正面

private:

	VECTOR* camera_pos_;		// 
	VECTOR pos_;				// 自身の座標
	VECTOR target_pos_;			// 注視点の座標

	VECTOR vel_;
	VECTOR target_vel_;

	float near_;
	float far_;

	float fov_;

	

};