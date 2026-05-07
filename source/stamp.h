#pragma once

class ObjectBase;
enum class BehaviorStatus;

class Stamp :public AttackBase
{
public:

	Stamp(std::weak_ptr<ObjectBase> owner, VECTOR* pos,float radius);

	~Stamp() override;

	void Init() override;

	BehaviorStatus Update() override;

	void Debug() override;

	virtual void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

private:



};