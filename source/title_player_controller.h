#pragma once
#include"physics_interface.h"

class AnimatorBase;
class Time;
class RigidBody;
class VariableTimer;

class TitlePlayerController : public IPhysicsEventReceiver
{
public:

	TitlePlayerController();

	~TitlePlayerController() override;

	void Awake();

	void Init();

	void Update();

	void LateUpdate();

	void Draw();

	void Debug();

	void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

	const VECTOR GetPos() const;

	const VECTOR GetHeadPos() const;

	std::shared_ptr<RigidBody> GetRigidBody() override;

	const float GetDeltaTime() const override;

private:

	void FirstPhaseUpdate();

	void SecondPhaseUpdate();

	void ThirdPhaseUpdate();

	void FourthPhaseUpdate();

	void FifthPhaseUpdate();

	void SixPhaseUpdate();

	void Setting();

private:

	enum class Phase
	{
		kFirst,
		kSecond,
		kThird,
		kFourth,
		kFifth,
		kSix,
	};

	const float kWalkSpeed = 0.1f;
	const float kHeadVertical = 10.f;	// ì™ÇÃçÇÇ≥Ç…çáÇÌÇπÇÈ

	std::shared_ptr<RigidBody> rigid_body_;
	std::shared_ptr<AnimatorBase> animator_;
	std::shared_ptr<Time> time_;
	std::shared_ptr<VariableTimer> offset_timer_;

	Phase phase_;

	VECTOR pos_;
	VECTOR scale_;
	VECTOR rotation_;

	VECTOR head_pos_;

	int model_handle_;

};