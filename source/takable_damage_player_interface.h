#pragma once

class ITakableDamageEnemy
{
public:

	virtual ~ITakableDamageEnemy() = default;
	virtual void OnDamageFromPlayer(float damage);

};