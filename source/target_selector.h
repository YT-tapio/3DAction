#pragma once

class IAttackTarget;
class AttackTargetRepository;

class TargetSelector
{
public:

	TargetSelector(std::weak_ptr<AttackTargetRepository> attack_target_repository,const Faction& target_faction);

	~TargetSelector();

	void Init();

	void Update();

	const IAttackTarget* GetAttackTarget() const;

private:

	std::weak_ptr<AttackTargetRepository> attack_target_repository_;
	IAttackTarget* target_;

	Faction target_faction_;

};