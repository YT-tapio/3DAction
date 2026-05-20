#include<memory>
#include"behavior_base.h"
#include"behavior_status.h"
#include"object_behavior.h"

ObjectBehavior::ObjectBehavior(std::weak_ptr<ObjectBase> owner)
	:BehaviorBase(owner)
	,my_owner_(owner)
{

}