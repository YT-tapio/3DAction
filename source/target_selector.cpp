#include<memory>
#include<vector>
#include"DxLib.h"
#include"faction.h"
#include"target_selector.h"
#include<unordered_map>
#include"attack_target_repository.h"
#include"attack_target_interface.h"

TargetSelector::TargetSelector(std::weak_ptr<AttackTargetRepository> attack_target_repository,const Faction& target_faction)
	: attack_target_repository_(attack_target_repository)
	, target_faction_(target_faction)
	, target_(nullptr)
{
	
}

TargetSelector::~TargetSelector()
{

}

void TargetSelector::Init()
{

}

void TargetSelector::Update()
{
	auto attack_target_repository = attack_target_repository_.lock();
	if (attack_target_repository == nullptr) { return; }
	// repositoryから複数の対象もらってターゲットを決める
	auto attack_targets = attack_target_repository->GetAttackTargets(target_faction_);
	float most_low_hp = 0.f;
	bool is_first = TRUE;
	for (auto attack_target : attack_targets)
	{
		if (attack_target == nullptr) { continue; }
		auto info = attack_target->GetAttackTargetInfo();
		if (is_first) 
		{
			is_first = FALSE;
			target_ = attack_target;
			most_low_hp = info.status.hp;
			continue;
		}
		if (most_low_hp < info.status.hp)
		{
			most_low_hp = info.status.hp;
			target_ = attack_target;
		}
	}
}

const IAttackTarget* TargetSelector::GetAttackTarget() const
{
	return target_;
}