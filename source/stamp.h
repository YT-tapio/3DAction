#pragma once

class ObjectBase;
class AttackInfoHolder;
enum class BehaviorStatus;
enum class AttackPhase;

class Stamp :public AttackBase
{
public:

	Stamp(std::weak_ptr<ObjectBase> owner, VECTOR* pos,float radius,std::string my_anim_name, float damage_rate, std::weak_ptr<AttackInfoHolder> owner_attack_info_holder);

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

	void ChangeAttackInfo(const AttackPhase& phase,const VECTOR& pos, const VECTOR& dir,const float& range);

private:

	std::weak_ptr<AttackInfoHolder> owner_attack_info_holder_;

	std::string my_anim_name_;

	float radius_;

	bool is_stamp_;

};