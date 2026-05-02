#pragma once

enum class JumpingAttackState;
class AttackBase;
class ObjectBase;
class IPhysicsEventReceiver;
class ConditionTimer;
class CharacterBase;

class JumpingAttack : public AttackBase
{
public:

	JumpingAttack(std::weak_ptr<ObjectBase> owner, VECTOR* pos, float min_coll_ratio, float max_coll_ratio,std::string my_anim_name);

	~JumpingAttack() override;

	void Init() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Draw() override;

	void Debug()override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object);

private:

	/// <summary>
	/// ジャンプする前
	/// </summary>
	/// <returns></returns>
	BehaviorStatus StandbyUpdate(std::shared_ptr<CharacterBase> owner);

	/// <summary>
	/// ジャンプ中
	/// </summary>
	/// <returns></returns>
	BehaviorStatus JumpingUpdate(std::shared_ptr<CharacterBase> owner);

	/// <summary>
	/// 空中で
	/// </summary>
	/// <returns></returns>
	BehaviorStatus AirStandbyUpdate(std::shared_ptr<CharacterBase> owner);

	/// <summary>
	/// 落ちる
	/// </summary>
	/// <returns></returns>
	BehaviorStatus FallingUpdate(std::shared_ptr<CharacterBase> owner);

	/// <summary>
	/// 当たり判定をオンするかどうか
	/// </summary>
	/// <returns></returns>
	const bool CheckActiveColl(std::shared_ptr<CharacterBase> owner) const;

	std::shared_ptr<ConditionTimer> condition_timer_;

	JumpingAttackState jumping_state_;

	VECTOR* coll_pos_;

	float jumping_timing_;	// ジャンプのタイミング：アニメーション基準
	float jumping_anim_stop_timing_;	// ジャンプ中のアニメーションをstopするタイミング

	std::string my_anim_name_;


};