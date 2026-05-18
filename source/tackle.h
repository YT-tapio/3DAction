#pragma once

enum class BehaviorStatus;
class AttackBase;
class IPhysicsEventReceiver;
class ConditionTimer;

class Tackle :public AttackBase
{
public:

	Tackle(std::weak_ptr<ObjectBase> owner,std::shared_ptr<RigidBody> rigid_body,const float time);

	~Tackle() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

private:

	// “–‚½‚è”»’è‚Ì”­¶ŠÔ
	std::shared_ptr<ConditionTimer> activate_timer_;

	std::string anim_;
	std::string tackle_anim_;

};