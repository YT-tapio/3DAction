#pragma once
#include"DxLib.h"
#include"status.h"

struct AttackTargetInfo
{
	VECTOR pos = VGet(0, 0, 0);
	Status status;
};