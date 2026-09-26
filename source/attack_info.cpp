#include"attack_info_holder.h"

AttackInfoHolder::AttackInfoHolder()
{

}

AttackInfoHolder::~AttackInfoHolder()
{

}

void AttackInfoHolder::SetAttackInfo(const AttackInfo& info)
{
	info_ = info;
}

const AttackInfo AttackInfoHolder::GetAttackInfo() const
{
	return info_;
}