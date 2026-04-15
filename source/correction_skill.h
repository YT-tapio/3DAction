#pragma once
#include"skill_base.h"

class CorrectionSkill : public SkillBase
{
public:

	CorrectionSkill(std::weak_ptr<Player> owner, std::shared_ptr<BehaviorBase> behavior);

	virtual ~CorrectionSkill() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:

	// 補正
	virtual void Correction();

private:





};