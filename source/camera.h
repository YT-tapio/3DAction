#pragma once

class Camera
{
public:

	Camera();

	~Camera();

	void Update();

	void Debug();

	VECTOR dir_;

private:

	VECTOR pos_;				// 自身の座標
	VECTOR target_pos_;		// 注視点の座標
						// カメラの正面
	
	float near_;
	float far_;

	float fov_;

	/// <summary>
	/// カメラのpos,near,farなどのセッティングを行う
	/// </summary>
	void Setting();

};