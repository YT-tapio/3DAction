#include<vector>
#include<memory>
#include"DxLib.h"
#include"area_action_base.h"
#include"check_my_area.h"
#include"object_base.h"

AreaActionBase::AreaActionBase(std::weak_ptr<ObjectBase> owner, std::shared_ptr<CheckMyArea> area, VECTOR* pos)
	: BehaviorBase(owner)
{
	my_area_ = area;
}

AreaActionBase::~AreaActionBase()
{

}

void AreaActionBase::Init()
{
	my_area_->Init();
}

void AreaActionBase::Update()
{
	auto my_area_objects = my_area_->GetMyAreaObject();

	for (auto& object : my_area_objects)
	{
		Action(object.lock());
	}


}

void AreaActionBase::Draw()
{

}

void AreaActionBase::Debug()
{

}

void AreaActionBase::Action(std::shared_ptr<ObjectBase> object)
{
	
}