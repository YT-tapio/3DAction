#pragma once

class ITakableHealPlayer
{
public:

	virtual ~ITakableHealPlayer() = default;

	virtual void OnHealFromPlayer(float heal);

};