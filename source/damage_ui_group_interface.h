#pragma once

class IDamageUIGroup
{
public:

	virtual void SpawnPlayerDamageUI(const VECTOR& pos, const float& damage);

	virtual void SpawnEnemyDamageUI(const VECTOR& pos, const float& damage);
};