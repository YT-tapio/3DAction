#pragma once

class IEnemyObserver
{
public:
	virtual ~IEnemyObserver() = default;

	virtual void OnTakeDamage(const float& damage);

	virtual void OnEnemyDeath();
};