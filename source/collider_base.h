#pragma once

#include<memory>

enum ColliderName;
class IPhysicsEventReceiver;
struct Contact;

class ColliderBase
{
public:

	ColliderBase(ColliderName name);

	virtual ~ColliderBase();

	virtual void Draw(const VECTOR& pos);

	virtual bool CheckCollision(const VECTOR& my_pos, const VECTOR& vel,const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll,Contact& contact);

	virtual VECTOR FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact);

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> my_object, std::shared_ptr<IPhysicsEventReceiver> hit_object);

	const ColliderName GetName() const;

private:

	ColliderName name_;

};