#pragma once

class ObjectBase;
enum class BehaviorStatus;

class Stamp :public AttackBase
{
public:

	Stamp(std::weak_ptr<ObjectBase> owner, VECTOR* pos,float radius,std::string my_anim_name);

	~Stamp() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Debug() override;

	void Exit() override;

	virtual void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

private:

	std::string my_anim_name_;

	bool is_stamp_;

};