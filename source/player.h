#pragma once
#include"character_base.h"
#include"physics_interface.h"

class RigidBody;
class InputBase;
class CheckMyArea;
class SkillBase;
class ObjectBase;

class Player : public CharacterBase , public IPhysicsEventReceiver
{
public:

	Player(VECTOR* camera_dir, std::shared_ptr<const InputBase> input);

	~Player() override;

	void Init() override;

	void Update() override;
	
	void LateUpdate() override;

	void ResetVelocity();

	void SetVelocity(const VECTOR& velocity);

	void SetRotation(const VECTOR& rotation);

	void SetDirection(const VECTOR& direction);

	void SetIsStop(bool flag);

	void Draw() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> obj) override;

	void OnGrounded(std::shared_ptr<IPhysicsEventReceiver> object) override;

	void OnUnGrounded(std::shared_ptr<IPhysicsEventReceiver> object) override;

	VECTOR* GetHeadPos();

	std::vector<std::weak_ptr<ObjectBase>> GetMyAreaObject();

	const std::shared_ptr<const InputBase> GetInput() const;

	const bool GetIsMove() const;

	const bool GetIsGround() const;

	const bool GetIsDash() const;

private:

	const float kSpeed = 0.3f;

	std::shared_ptr<RigidBody> rigid_body_;
	std::shared_ptr<const InputBase> input_;
	std::shared_ptr<CheckMyArea> my_area_;
	std::shared_ptr<SkillBase> skill_;

	VECTOR* camera_dir_;
	VECTOR hand_pos_;
	VECTOR head_pos_;

	VECTOR attack_target_pos_;

	float target_rot_y_;
	float fall_speed_;

	bool is_move_;
	bool is_dash_;
	bool is_ground_;
	bool* is_punch_;
	bool is_stop_;
	bool is_attack_target_in_range_;		// çUåÇëŒè€Ç™îÕàÕì‡Ç…Ç¢ÇÈÇÃÇ©

	// ä÷êîåQ

	void LoadFile();

	void Move();

	void Gravity();

	void UpdateBone();

	void DecideAttackTarget();

};
