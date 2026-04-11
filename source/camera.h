#pragma once
#include"physics_interface.h"

class RigidBody;

class Camera : public IPhysicsEventReceiver
{
public:

	Camera();

	~Camera() override;

	void Init();

	void Update();

	void Debug();

	/// <summary>
	/// カメラのpos,near,farなどのセッティングを行う
	/// </summary>
	void Setting();

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> obj) override;

	VECTOR* GetPos();

	VECTOR* GetTargetPos();

	VECTOR dir_;// カメラの正面

private:

	std::shared_ptr<RigidBody> rigid_body_;

	VECTOR pos_;				// 自身の座標
	VECTOR target_pos_;			// 注視点の座標

	VECTOR vel_;
	VECTOR target_vel_;

	float near_;
	float far_;

	float fov_;

	

};