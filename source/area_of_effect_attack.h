#pragma once

class ObjectBase;
class IPhysicsEventReceiver;
class ConditionTimer;
enum class BehaviorStatus;
enum class AreaOfEffectAttackState;

class AreaOfEffectAttack : public AttackBase
{
public:
	AreaOfEffectAttack(std::weak_ptr<ObjectBase> owner,
		float min_coll_ratio,float max_coll_ratio,VECTOR effect_scale,
		float hit_radius, int effect_id,float activate_time);

	~AreaOfEffectAttack() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;


private:

	/// <summary>
	/// “–‚½‚è”»’è‚ªo‚é‘O
	/// </summary>
	BehaviorStatus UpdateCharge();

	/// <summary>
	/// “–‚½‚è”»’è‚ªs‚í‚ê‚Ä‚¢‚éÅ’†
	/// </summary>
	BehaviorStatus UpdatePlay();

private:

	std::shared_ptr<ConditionTimer> activate_timer_;
	
	AreaOfEffectAttackState state_;

	VECTOR effect_pos_;
	VECTOR effect_rot_;
	VECTOR effect_scale_;

	int effect_id_;
};