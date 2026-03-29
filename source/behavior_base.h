#pragma once

class ObjectBase;

class BehaviorBase
{
public:

	BehaviorBase(std::weak_ptr<ObjectBase> owner);

	virtual ~BehaviorBase();

	virtual void Init();

	virtual void Update();

	virtual void Draw();

	virtual void Debug();

	std::weak_ptr<ObjectBase> GetOwner();

protected:

	std::weak_ptr<ObjectBase> owner_;

private:

	

};