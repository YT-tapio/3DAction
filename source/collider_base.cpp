#include"DxLib.h"
#include"physics_interface.h"
#include"collider_name.h"
#include"collider_base.h"
#include"contact.h"
#include"vector_assistant.h"
ColliderBase::ColliderBase(ColliderName name)
	:name_(name)
{

}

ColliderBase::~ColliderBase()
{

}

void ColliderBase::Draw(const VECTOR& pos)
{

}

bool ColliderBase::CheckCollision(const VECTOR& my_pos, const VECTOR& vel,const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll,Contact& contact)
{
	

	return TRUE;
}

VECTOR ColliderBase::FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact)
{
	return VectorAssistant::VGetZero();
}

void ColliderBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> my_object, std::shared_ptr<IPhysicsEventReceiver> hit_object)
{
	my_object->OnHit(hit_object);
}

const ColliderName ColliderBase::GetName() const
{
	return name_;
}
