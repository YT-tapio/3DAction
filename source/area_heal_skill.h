#pragma once
#include"skill_base.h"

class AreaHealSkill : public SkillBase
{
public:

	AreaHealSkill(std::weak_ptr<Player> owner,VECTOR* pos,const float radius, SkillType type, float cool_time);

	~AreaHealSkill() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

protected:



private:

	bool CheckIsAreaHeal(std::shared_ptr<Player> owner);


};