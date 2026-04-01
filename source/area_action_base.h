#pragma once
#include"behavior_base.h"

class ObjectBase;
class CheckMyArea;


class AreaActionBase : public BehaviorBase
{
public:

	AreaActionBase(std::weak_ptr<ObjectBase> owner,std::shared_ptr<CheckMyArea> area,VECTOR* pos);
	
	virtual ~AreaActionBase() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:

	virtual void Action(std::shared_ptr<ObjectBase> object);

	std::shared_ptr<CheckMyArea> my_area_;


private:



};