#pragma once
class IEnemyObserver;

class IEnemyController
{
public:

	virtual void AddBossObserver(IEnemyObserver* observer);

	virtual const VECTOR GetBossCenterPos() const;

	virtual const VECTOR GetBossFrontDir() const;
};