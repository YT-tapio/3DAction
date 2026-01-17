#include<iostream>
#include"DxLib.h"
#include"collider_group.h"
#include"collider_base.h"
#include"physics_interface.h"

ColliderGroup::ColliderGroup(std::vector<std::shared_ptr<ColliderBase>> colliders)
	:colliders_(colliders)
{
	
}

ColliderGroup::~ColliderGroup()
{

}

const std::vector<std::shared_ptr<ColliderBase>> ColliderGroup::GetColliders() const
{
	return colliders_;
}

