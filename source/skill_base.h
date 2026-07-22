#pragma once
#include"condition_timer.h"

class Player;
class BehaviorBase;

class SkillBase
{
public:

	SkillBase(std::weak_ptr<Player> owner,std::shared_ptr<BehaviorBase> behavior, float cool_time = 0.f);

	virtual ~SkillBase();

	virtual void Init();

	virtual void Update();

	virtual void Draw();

	virtual void Debug();

	const float GetCoolTiemRatio() const;

	const bool CanUseSkill() const;

protected:

	const bool CheckMyOwner() const;

protected:

	std::weak_ptr<Player> owner_;
	std::shared_ptr<BehaviorBase> behavior_;

	std::shared_ptr<ConditionTimer> cool_time_;
	
	bool is_active_;

	bool can_use_;

private:



};