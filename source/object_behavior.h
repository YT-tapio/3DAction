#pragma once

class BehaviorBase;
class ObjectBase;

class ObjectBehavior : public BehaviorBase
{
public:

	ObjectBehavior(std::weak_ptr<ObjectBase> owner);

	virtual ~ObjectBehavior() override {};

	virtual void Init() override {};

	virtual void Entry() override {};

	virtual BehaviorStatus Update() override { return BehaviorStatus::kFailure; };

	virtual void Exit() override {};

	virtual void Draw() override {};

	virtual void Debug() override {};

protected:

	std::weak_ptr<ObjectBase> my_owner_;

private:


};