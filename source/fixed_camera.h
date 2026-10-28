#pragma once
#include"virtual_camera_base.h"
#include"move_transition_method.h"

class VariableTimer;

// 固定のカメラ
class FixedCamera : public VirtualCameraBase
{
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos">main_camera_pos</param>
	/// <param name="target_pos">main_camera_target_pos</param>
	/// <param name="my_pos">自分のpos</param>
	/// <param name="my_target_pos">自分のtarget_pos</param>
	/// <param name="method">変化方法</param>
	/// <param name="speed">変化する際のスピード(time_lerpの際はその時間が遷移時間になる)</param>
	FixedCamera(VECTOR* pos, VECTOR* target_pos, const VECTOR& my_pos, const VECTOR& my_target_pos,MoveTransitionMethod method,const float& speed = 0.f);

	~FixedCamera() override;

	void Init() override;

	void Update() override;

private:

	void MomentUpdate();

	void LerpUpdate();

	void TimeLerpUpdate();

	void DampUpdate();

private:

	std::shared_ptr<VariableTimer> timer_;

	MoveTransitionMethod method_;

	VECTOR my_pos_;
	VECTOR my_target_pos_;

	float speed_;

};