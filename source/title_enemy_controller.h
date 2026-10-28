#pragma once
#include"physics_interface.h"

class AnimatorBase;
class Time;
class VariableTimer;

class TitleEnemyController : public IPhysicsEventReceiver
{
public:

	TitleEnemyController();

	~TitleEnemyController() override;

	void Awake();

	void Init();

	void Update();

	void LateUpdate();

	void Draw();

	void Debug();

	void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

	std::shared_ptr<RigidBody> GetRigidBody() override;

private:

	void Move();

	void Setting();

	void FirstPhaseUpdate();

	void SecondPhaseUpdate();

	void ThirdPhaseUpdate();

	void FourthPhaseUpdate();

	void FifthPhaseUpdate();

private:

	enum class Phase
	{
		kFirst,
		kSecond,
		kThird,
		kFourth,
		kFifth
	};


	const float kDashSpeed = 0.5f;

	std::shared_ptr<AnimatorBase> animator_;
	std::shared_ptr<Time> time_;
	std::shared_ptr<VariableTimer> timer_;

	std::shared_ptr<RigidBody> rigid_body_;

	VECTOR pos_;
	VECTOR scale_;
	VECTOR rotation_;

	Phase phase_;

	int model_handle_;

};