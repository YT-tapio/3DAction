#pragma once
#include"behavior_interface.h"
#include"skill_type.h"

class AIInput;
//スキルを実行する(inputのスキルに対応しているフラグをonにする)
class ExecuteSkill : public IBehavior
{
public:

	ExecuteSkill(AIInput* input,const SkillType& type);

	~ExecuteSkill() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	AIInput* input_;
	SkillType type_;

};