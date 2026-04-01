#pragma once

class ITakableHealEnemy
{
	virtual ~ITakableHealEnemy() = default;

	virtual void OnHealFromEnemy(float heal);
};