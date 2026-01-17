#pragma once

#include<memory>

enum ColliderName;
class IPhysicsEventReceiver;

class ColliderBase
{
public:

	ColliderBase(ColliderName name);

	virtual ~ColliderBase();

	virtual void Draw(const VECTOR& pos);

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> my_object, std::shared_ptr<IPhysicsEventReceiver> hit_object);

	const ColliderName GetName() const;

private:

	ColliderName name_;

};