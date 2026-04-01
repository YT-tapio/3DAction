#pragma once

class ITakableDamageEnemy
{
public:

	virtual ~ITakableDamageEnemy() = default;
	virtual void OnDamageFromEnemy(float damage);

};