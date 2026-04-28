#pragma once

enum class BehaviorStatus;
class ObjectBase;

class BehaviorBase
{
public:

	BehaviorBase(std::weak_ptr<ObjectBase> owner);

	virtual ~BehaviorBase();

	virtual void Init();

	virtual BehaviorStatus Update();

	virtual void Exit();

	virtual void Draw();

	virtual void Debug();

	void Active();

	std::weak_ptr<ObjectBase> GetOwner();

protected:

	std::weak_ptr<ObjectBase> owner_;

	bool is_active_;

private:

	

};