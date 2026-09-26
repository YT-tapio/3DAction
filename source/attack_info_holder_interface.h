#pragma once
#include"attack_info.h"

class IAttackInfoHolder
{
public:

	virtual ~IAttackInfoHolder() = default;

	virtual const AttackInfo GetAttackInfo() const;

};