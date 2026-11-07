#pragma once

class IPopupUIGroup
{
public:

	virtual void SpawnPlayerDamageUI(const VECTOR& pos, const float& damage,const bool is_critical) {}

	virtual void SpawnPlayerHealUI(const VECTOR& pos, const float& heal) {}

	virtual void SpawnEnemyDamageUI(const VECTOR& pos, const float& damage, const bool is_critical) {}

	virtual void SpawnEnemyHealUI(const VECTOR& pos, const float& heal) {}
};