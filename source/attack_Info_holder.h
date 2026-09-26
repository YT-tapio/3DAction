#pragma once
#include"attack_info.h"

class AttackInfoHolder
{
public:

	AttackInfoHolder();

	~AttackInfoHolder();

	void SetAttackInfo(const AttackInfo& info);

	const AttackInfo GetAttackInfo() const;

private:

	AttackInfo info_;


};