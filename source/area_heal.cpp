#include<vector>
#include<memory>
#include"DxLib.h"
#include"area_heal.h"
#include"check_my_area.h"

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

void AreaHeal::Action(std::shared_ptr<ObjectBase> object)
{
	
}
