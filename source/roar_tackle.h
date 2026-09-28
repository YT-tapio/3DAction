#pragma once

class ObjectBase;
class RigidBody;
class IAttackRangeGroup;
class AttackInfoHolder;
enum class AttackPhase;

// ‹©‚ñ‚Å‚©‚ç“Ëi‚·‚é
class RoarTackle : public Tackle
{
public:

	RoarTackle(std::weak_ptr<ObjectBase> owner, std::shared_ptr<RigidBody> rigid_body,
		std::string anim_name, const float time, const float speed, float damage_rate, std::shared_ptr<IAttackRangeGroup> attack_range_group,std::weak_ptr<AttackInfoHolder> owner_attack_info_holder);

	~RoarTackle();

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	void RoarUpdate();

	BehaviorStatus TackleUpdate();

private:

	enum class TackleState
	{
		roar,
		tackle
	};

	std::shared_ptr<IAttackRangeGroup> attack_range_group_;

	std::weak_ptr<AttackInfoHolder>  owner_attack_info_holder_;

	VECTOR attack_dir_;	// UŒ‚•ûŒü

	TackleState tackle_state_;

	std::string roar_anim_name_;

	int attack_range_ui_id_;	// ©•ª‚ª•`‰æ‚ğˆË—Š‚µ‚½‚à‚Ì‚Ì”Ô†

	bool is_end_;
};