#include<vector>
#include<memory>
#include"DxLib.h"
#include"area_heal.h"
#include"check_my_area.h"
#include"behavior_status.h"

AreaHeal::AreaHeal(std::weak_ptr<ObjectBase> owner,std::shared_ptr<CheckMyArea> area,VECTOR* pos)
	: AreaActionBase(owner,area,pos)
{

}

AreaHeal::~AreaHeal()
{

}

void AreaHeal::Draw()
{

}

void AreaHeal::Debug()
{

}

BehaviorStatus AreaHeal::Action(std::shared_ptr<ObjectBase> object)
{
	return BehaviorStatus::kFailure;
}
