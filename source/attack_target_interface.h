#pragma once
#include"attack_target_info.h"

class IAttackTarget
{
public:

	virtual ~IAttackTarget() = default;

	virtual const AttackTargetInfo GetAttackTargetInfo() const;

};