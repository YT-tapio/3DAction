#pragma once

class IDamageUIGroup
{
public:

	virtual void SpawnPlayerDamageUI(const VECTOR& pos, const float& damage,const bool is_critical) {}

	virtual void SpawnEnemyDamageUI(const VECTOR& pos, const float& damage, const bool is_critical) {}
};