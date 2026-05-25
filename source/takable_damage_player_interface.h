#pragma once

enum class AttackType;

/// <summary>
/// player‚©‚çUŒ‚‚ğó‚¯‚é
/// </summary>
class ITakableDamagePlayer
{
public:

	virtual ~ITakableDamagePlayer() = default;
	virtual void OnDamageFromPlayer(float damage,AttackType type);

};