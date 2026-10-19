
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

VECTOR IPlayerGroup::GetPlayerPos(const std::string& name)
{
	VECTOR player_pos = VGet(0.f, 0.f, 0.f);
	return player_pos;
}

VECTOR IPlayerGroup::MostNearPlayerPos(const VECTOR& other_pos)
{
	VECTOR pos = VGet(0.f, 0.f, 0.f);
	return pos;
}

std::string IPlayerGroup::MostNearPlayerName(const VECTOR& other_pos)
{
	return "";
}