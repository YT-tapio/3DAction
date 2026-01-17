#include"DxLib.h"
#include"physics_interface.h"
#include"collider_name.h"
#include"collider_base.h"

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

void ColliderBase::OnHit(std::shared_ptr<IPhysicsEventReceiver> my_object, std::shared_ptr<IPhysicsEventReceiver> hit_object)
{
	my_object->OnHit(hit_object);
}

const ColliderName ColliderBase::GetName() const
{
	return name_;
}
