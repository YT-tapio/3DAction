#pragma once
#include"area_action_base.h"

enum class BehaviorStatus;
class ObjectBase;

class AreaHeal : public AreaActionBase
{
public:

	AreaHeal(std::weak_ptr<ObjectBase> owner, std::shared_ptr<CheckMyArea> area, VECTOR* pos);

	virtual ~AreaHeal() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:


	virtual BehaviorStatus Action(std::shared_ptr<ObjectBase> object)override;


private:



};