#pragma once

#include"attack_base.h"

enum class BehaviorStatus;
class ObjectBase;

class Punch : public AttackBase
{
public:

	Punch(std::weak_ptr<ObjectBase> owner,VECTOR* pos, std::string my_anim_name,
		float min_coll_ratio, float max_coll_ratio,std::shared_ptr<RigidBody> body);

	~Punch()override;

	void Init() override;

	BehaviorStatus Update() override;
	
	void Exit() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

private:

	VECTOR* pos_;

	std::string my_anim_name_;

};