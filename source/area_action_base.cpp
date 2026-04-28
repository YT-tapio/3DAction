#include<vector>
#include<memory>
#include"DxLib.h"
#include"area_action_base.h"
#include"check_my_area.h"
#include"object_base.h"
#include"behavior_status.h"

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

BehaviorStatus AreaActionBase::Update()
{
	auto my_area_objects = my_area_->GetMyAreaObject();

	//TODO : Actionä÷êîbehaviorstatusÇï‘Ç∑ÇÊÇ§Ç…
	for (auto& object : my_area_objects)
	{
		Action(object.lock());
	}

	return BehaviorStatus::kFailure;
}

void AreaActionBase::Draw()
{

}

void AreaActionBase::Debug()
{

}

BehaviorStatus AreaActionBase::Action(std::shared_ptr<ObjectBase> object)
{
	return BehaviorStatus::kFailure;
}