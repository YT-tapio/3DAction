#pragma once

#include"skill_base.h"

class AvoidSkill : public SkillBase
{
public:

	AvoidSkill(std::weak_ptr<Player> owner, float speed);

	~AvoidSkill() override;

	void Init() override;

	void Update() override;

	void Debug() override;

private:

	bool CheckIsAvoid(std::shared_ptr<Player> owner);

	void DecideVelocity(std::shared_ptr<Player> owner);

	float speed_;

};