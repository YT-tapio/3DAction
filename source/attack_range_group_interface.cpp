#include<functional>
#include"DxLib.h"
#include"attack_range_group_interface.h"


int IAttackRangeGroup::CircleDrawRequest(const VECTOR& pos, const VECTOR& scale, const float& time, std::function<bool()>end_function)
{
	return -1;
}

int IAttackRangeGroup::RectangleDrawRequest(const VECTOR& pos, const VECTOR& scale, const VECTOR& dir, const float& time, std::function<bool()> end_function)
{
	return -1;
}

void IAttackRangeGroup::CircleSetPos(const int& id, const VECTOR& pos)
{

}

void IAttackRangeGroup::RectangleSetPos(const int& id, const VECTOR& pos)
{

}

void IAttackRangeGroup::RectangleSetDir(const int& id, const VECTOR& dir)
{

}