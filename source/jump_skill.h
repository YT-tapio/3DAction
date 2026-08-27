#pragma once
#include"skill_base.h"

class JumpSkill : public SkillBase
{
public:

	JumpSkill(std::weak_ptr<Player> owner,std::pair<float,float> timing,const float up_speed,float cool_time = 0.f);

	~JumpSkill() override;

	void Init() override;

	void Update() override;

private:

	const bool IsPush() const;

private:

	enum class JumpState
	{
		ready,
		jump
	};

	JumpState state_;

};