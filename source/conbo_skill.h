#pragma once
#include"close_correction_skill.h"

class BehaviorBase;
class ObjectBase;
class Player;
class ConboAction;

class ConboSkill : public CloseCorrectionSkill
{
public:

	ConboSkill(std::weak_ptr<Player> owner, std::shared_ptr<BehaviorBase> behavior);

	~ConboSkill() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

private:

	bool IsStartConboAction(std::shared_ptr<ConboAction> conbo_action);

	bool CheckGoNextConbo(std::shared_ptr<ConboAction> conbo_action);

};