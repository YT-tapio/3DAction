#pragma once

class IPhysicsEventReceiver;

class BehaviorBase
{
public:

	BehaviorBase(std::weak_ptr<IPhysicsEventReceiver> owner);

	virtual ~BehaviorBase();

	virtual void Init();

	virtual void Update();

	virtual void Debug();

protected:

	std::weak_ptr<IPhysicsEventReceiver> owner_;

private:

	

};