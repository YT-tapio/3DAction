#pragma once
#include"skill_base.h"

class JumpInfiteAttackSkill :public SkillBase
{
public:

	JumpInfiteAttackSkill(std::weak_ptr<Player> owner,SkillType type,float cool_time = 0.f);

	~JumpInfiteAttackSkill() override;

	void Init() override;

	void Update() override;

	void Debug() override;

private:

	bool IsPush();

private:

	


};
