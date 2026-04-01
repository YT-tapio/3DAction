#pragma once
#include"area_heal.h"

//player‚©‚çheal‚ðŽó‚¯‚é‚à‚Ì‚ðheal‚·‚é
class AreaHealGivePlayer : public AreaHeal
{
public:

	AreaHealGivePlayer(std::weak_ptr<ObjectBase> owner, std::shared_ptr<CheckMyArea> area, VECTOR* pos);

	~AreaHealGivePlayer() override;

	void Draw() override;

	void Debug() override;

protected:

	virtual void Action(std::shared_ptr<ObjectBase> object)override;

private:



};
