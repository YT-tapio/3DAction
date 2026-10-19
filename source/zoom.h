#pragma once
#include<functional>

class VariableTimer;

class Zoom
{
public:

	Zoom();

	~Zoom();

	void Init();

	void Update();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="target_fov">ターゲットの視野角(ラジアン角)</param>
	/// <param name="zoom_time">何秒でズームさせるか</param>
	void Activate(const float& target_fov, const float& time,const float& active_time);
	
	void SetCurrentFov(const float& current_fov);

	// ズーム量
	const float GetZoomValue() const;

private:

	void ZoomInUpdate();

	void ZoomUpdate();

	void ZoomOutUpdate();

private:

	enum class ZoomState
	{
		kNotActive,	// 何もなし
		kZoomIn,	// ズームイン
		kZoom,		// ズーム中
		kZoomOut,	// ズームアウト
	};

	
	std::unique_ptr<VariableTimer> zoom_in_timer_;
	std::unique_ptr<VariableTimer> zoom_timer_;	//何秒ズームを行うか
	std::unique_ptr<VariableTimer> zoom_out_timer_;
	ZoomState state_;

	float current_fov_;

	float target_fov_;
	float zoom_value_;

	bool is_active_;
	bool is_zoom_;
};