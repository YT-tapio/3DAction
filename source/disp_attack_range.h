#pragma once

class BehaviorBase;

class DispAttackRange : public BehaviorBase
{
public:

	DispAttackRange(std::weak_ptr<ObjectBase> owner,VECTOR* pos,const VECTOR& attack_range_scale, 
		std::function<bool()> end_function,const float& time);

	~DispAttackRange() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Draw() override;

	void Debug() override;

private:

	std::function<bool()> end_function_;	// I—¹ğŒ
	VECTOR *pos_;							// “–‚½‚è”»’è‚Ìpos
	VECTOR attack_range_scale_;		// “–‚½‚è”»’è‚Ì‘å‚«‚³

	float time_;
};