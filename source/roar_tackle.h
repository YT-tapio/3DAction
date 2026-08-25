#pragma once

class ObjectBase;
class RigidBody;

// ‹©‚ñ‚Å‚©‚ç“Ëi‚·‚é
class RoarTackle : public Tackle
{
public:

	RoarTackle(std::weak_ptr<ObjectBase> owner, std::shared_ptr<RigidBody> rigid_body,
		std::string anim_name, const float time, const float speed, float damage_rate);

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

	VECTOR attack_dir_;	// UŒ‚•ûŒü

	TackleState tackle_state_;

	std::string roar_anim_name_;

	int attack_range_ui_id_;	// ©•ª‚ª•`‰æ‚ğˆË—Š‚µ‚½‚à‚Ì‚Ì”Ô†

	bool is_end_;
};