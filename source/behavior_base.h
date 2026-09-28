#pragma once
#include"behavior_interface.h"

enum class BehaviorStatus;
class ObjectBase;

class BehaviorBase : public IBehavior
{
public:

	BehaviorBase(std::weak_ptr<ObjectBase> owner);

	virtual ~BehaviorBase() override;

	virtual void Init() override;

	virtual void Entry() override;

	virtual BehaviorStatus Update() override;

	virtual void Exit() override;

	virtual void Draw() override;

	virtual void Debug() override;

	void Active();

	std::weak_ptr<ObjectBase> GetOwner();

protected:

	std::weak_ptr<ObjectBase> owner_;

	bool is_active_;

private:

	

};