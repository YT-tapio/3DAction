#pragma once
#include"skill_base.h"

class BehaviorBase;
class ObjectBase;
class Player;
class ConboAction;

class ConboSkill : public SkillBase
{
public:

	ConboSkill(std::weak_ptr<Player> owner, std::shared_ptr<BehaviorBase> behavior,float approach_speed, float approach_ratio);

	~ConboSkill() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

private:

	bool IsStartConboAction(std::shared_ptr<ConboAction> conbo_action);

	bool CheckGoNextConbo(std::shared_ptr<ConboAction> conbo_action);

	// コンボの攻撃の補正を格納している
	std::unordered_map<int, std::unordered_map<float, float>> approach_speed_ratio_mp_;

	float approach_speed_;			// 敵に近づく際のスピード
	float approach_ratio_;			// どれくらいの距離で補正をするかの割合
};