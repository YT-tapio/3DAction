#pragma once

enum class JumpingAttackState;
class AttackBase;
class ObjectBase;
class IPhysicsEventReceiver;
class ConditionTimer;

class JumpingAttack : public AttackBase
{
public:

	JumpingAttack(std::weak_ptr<ObjectBase> owner,float min_coll_ratio, float max_coll_ratio);

	~JumpingAttack() override;

	void Init() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Draw() override;

	void Debug()override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object);

private:

	std::shared_ptr<ConditionTimer> condition_timer_;

	JumpingAttackState jumping_state_;

	float jumping_timing_;	// ジャンプのタイミング：アニメーション基準
	float falling_timing_;	// 落下のタイミング：アニメーション基準
};