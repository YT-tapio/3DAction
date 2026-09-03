#include"DxLib.h"
#include"player_group_interface.h"

VECTOR* IPlayerGroup::GetCurrentPlayerHeadPos()
{
	VECTOR pos = VGet(0.f, 0.f, 0.f);
	return &pos;
}

VECTOR* IPlayerGroup::GetCurrentPlayerFrontDir()
{
	VECTOR dir = VGet(0.f, 0.f, 0.f);
	return &dir;
}

VECTOR IPlayerGroup::MostNearPlayerPos(const VECTOR& other_pos)
{
	VECTOR pos = VGet(0.f, 0.f, 0.f);
	return pos;
}