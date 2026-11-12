#pragma once
#include"faction.h"

class IAttackTarget;

class AttackTargetRepository
{
public:

	AttackTargetRepository();

	~AttackTargetRepository();

	void AddTarget(const Faction& faction, IAttackTarget* attack_target);

	const std::vector<IAttackTarget*> GetAttackTargets(const Faction& faction) const;

private:

	std::unordered_map<Faction, std::vector<IAttackTarget*>> faction_attack_targets_mp_;

};