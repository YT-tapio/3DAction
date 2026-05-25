#pragma once

/// <summary>
/// enemy‚©‚çƒ_ƒ[ƒW‚ğó‚¯‚é
/// </summary>
class ITakableDamageEnemy
{
public:

	virtual ~ITakableDamageEnemy() = default;
	virtual void OnDamageFromEnemy(float damage);

};