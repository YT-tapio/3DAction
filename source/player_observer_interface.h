#pragma once

class IPlayerObserver
{
public:
	virtual ~IPlayerObserver() = default;

	virtual void OnPlayerJustAvoid();

	virtual void OnPlayerAvoidCollect();

	virtual void OnPlayerDeath();
};