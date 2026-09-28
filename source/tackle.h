#pragma once


class AttackBase;
class IPhysicsEventReceiver;
class ConditionTimer;
class AttackInfoHolder;
enum class AttackPhase;
enum class BehaviorStatus;

class Tackle :public AttackBase
{
public:

	Tackle(std::weak_ptr<ObjectBase> owner,std::shared_ptr<RigidBody> rigid_body,
		std::string anim_name,const float time, const float speed, float damage_rate, std::weak_ptr<AttackInfoHolder> owner_attack_info_holder);

	virtual ~Tackle() override;

	virtual void Init() override;

	virtual void Entry() override;

	virtual BehaviorStatus Update() override;

	virtual void Exit() override;

	void Debug() override;

	void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

	void OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object) override;

	void OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object) override;

protected:

	void ChangeAttackInfo(const AttackPhase& phase, const VECTOR& pos, const VECTOR& dir, const float& range);

private:

	// ìñÇΩÇËîªíËÇÃî≠ê∂éûä‘
	std::shared_ptr<ConditionTimer> activate_timer_;
	std::weak_ptr<AttackInfoHolder> owner_attack_info_holder_;

	VECTOR vel_;
	VECTOR offset_vel_;
	std::string anim_name_;

	float speed_;
	
};