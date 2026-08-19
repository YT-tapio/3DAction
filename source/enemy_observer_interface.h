#pragma once

class IEnemyObserver
{
public:
	virtual ~IEnemyObserver() = default;

	virtual void OnEnemyDeath();
};