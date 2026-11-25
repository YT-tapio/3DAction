#pragma once
#include"behavior_interface.h"
#include"physics_interface.h"

class AnimatorBase;
class RigidBody;
class ConditionTimer;

class GrabPlayer : public IBehavior , public IPhysicsEventReceiver
{
public:

	GrabPlayer(std::weak_ptr<AnimatorBase> owner_animator,std::weak_ptr<RigidBody> owner_rigid_body,VECTOR* owner_pos,VECTOR* target_pos,const float& speed, const float& time);

	~GrabPlayer() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

	std::shared_ptr<RigidBody> GetRigidBody() override;

private:

	std::weak_ptr<AnimatorBase> owner_animator_;
	std::weak_ptr<RigidBody> owner_rigid_body_;

	std::shared_ptr<RigidBody> rigid_body_;

	std::unique_ptr<ConditionTimer> timer_;

	VECTOR* owner_pos_;
	VECTOR* target_pos_;
	VECTOR dir_;
	VECTOR vel_;

	float speed_;

	
	bool is_end_; // èIóπ

};