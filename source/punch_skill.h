#pragma once
#include"skill_base.h"

class PunchSkill : public SkillBase
{
public:

	PunchSkill(std::weak_ptr<Player>owner,VECTOR* pos,const float r);

	~PunchSkill() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

protected:


private:



};