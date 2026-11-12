#include<vector>
#include<unordered_map>
#include"attack_target_repository.h"

AttackTargetRepository::AttackTargetRepository()
{

}

AttackTargetRepository::~AttackTargetRepository()
{
	faction_attack_targets_mp_.clear();
}

void AttackTargetRepository::AddTarget(const Faction& faction,IAttackTarget* attack_target)
{
	// óvëfÇêVÇµÇ≠í«â¡(èdï°Ç»ÇµÇ≈)
	auto& targets = faction_attack_targets_mp_[faction];

	if (std::find(targets.begin(), targets.end(), attack_target) == targets.end())
	{
		targets.emplace_back(attack_target);
	}
}

const std::vector<IAttackTarget*> AttackTargetRepository::GetAttackTargets(const Faction& faction) const
{
	auto faction_attack_targets = faction_attack_targets_mp_.find(faction);

	if (faction_attack_targets == faction_attack_targets_mp_.end()) 
	{
		std::vector<IAttackTarget*> attack_targets;
		return attack_targets;
	}

	return faction_attack_targets->second;
}