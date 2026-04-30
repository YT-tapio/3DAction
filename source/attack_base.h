#pragma once
#include"behavior_base.h"
#include"physics_interface.h"

enum class BehaviorStatus;
class ObjectBase;
class RigidBody;

class AttackBase : public BehaviorBase , public IPhysicsEventReceiver
{
public:

	AttackBase(std::weak_ptr<ObjectBase> owner,float min_coll_ratio, float max_coll_ratio);

	~AttackBase() override;

	void Init() override;

	BehaviorStatus Update() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

protected:

	std::shared_ptr<RigidBody> rigid_body_;

	float min_coll_ratio_;	//当たり判定の発動タイミング：アニメーション基準
	float max_coll_ratio_;	//当たり判定の終了タイミング：アニメーション基準

private:

	

};