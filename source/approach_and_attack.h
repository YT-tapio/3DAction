#pragma once
#include"attack_base.h"

class ObjectBase;
class EnemyBase;
class IPhysicsEventReciever;

/// <summary>
/// 近づきながら攻撃をする
/// アニメーションを基準にアプローチするタイミングを決める
/// </summary>
class ApproachAndAttack : public AttackBase
{
public:

	ApproachAndAttack(std::weak_ptr<ObjectBase> owner,const float& min_coll_ratio, const float& max_coll_ratio, const float& damage_rate,
		const std::string& my_anim_name,const float approach_timing, const float approach_speed, const std::string& collider_tag);

	~ApproachAndAttack() override;;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Debug() override;

	void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

	void OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object) override;

	void OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object) override;

private:

	void Approach(std::shared_ptr<EnemyBase> owner);

	void UpdateCollisionPos(std::shared_ptr<EnemyBase> owner);

private:

	VECTOR pos_;

	std::string my_anim_name_;
	std::string collider_tag_;

	float approach_timing_;
	float approach_speed_;

	bool is_approached_;

};
