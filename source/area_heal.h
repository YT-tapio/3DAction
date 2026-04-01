#pragma once
#include"area_action_base.h"

class ObjectBase;

class AreaHeal : public AreaActionBase
{
public:

	AreaHeal(std::weak_ptr<ObjectBase> owner, std::shared_ptr<CheckMyArea> area, VECTOR* pos);

	virtual ~AreaHeal() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:


	virtual void Action(std::shared_ptr<ObjectBase> object)override;


private:



};