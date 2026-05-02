#pragma once
#include"character_base.h"
#include"physics_interface.h"
#include"takable_heal_player_interface.h"
#include"takable_damage_enemy_interface.h"
#include"input_change_interface.h"

class RigidBody;
class InputBase;
class CheckMyArea;
class SkillBase;
class ObjectBase;
class BehaviorBase;

class Player : public CharacterBase , public IPhysicsEventReceiver
	,public ITakableHealPlayer,public ITakableDamageEnemy,public IInputChange
{
public:

	Player(VECTOR* camera_dir, std::shared_ptr<const InputBase> input,const std::string name);

	~Player() override;

	void Init() override;

	void Update() override;
	
	void LateUpdate() override;

	void ResetVelocity();

	void SetTragetVelocity(const VECTOR& velocity);

	void SetVelocity(const VECTOR& velocity);

	void SetRotation(const VECTOR& rotation);

	void SetDirection(const VECTOR& direction);

	void SetIsStop(bool flag);

	void Draw() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> obj) override;

	void OnGrounded(std::shared_ptr<IPhysicsEventReceiver> object) override;

	void OnUnGrounded(std::shared_ptr<IPhysicsEventReceiver> object) override;

	void OnHealFromPlayer(float heal) override;

	void OnDamageFromEnemy(float damage) override;

	void InputChange(std::shared_ptr<InputBase> input) override;

	VECTOR* GetHeadPos();

	VECTOR* GetRightHandPos();

	VECTOR* GetLeftHandPos();

	VECTOR* GetPosPtr();

	std::vector<std::weak_ptr<ObjectBase>> GetMyAreaObject();

	const std::shared_ptr<const InputBase> GetInput() const;

	const float GetDetectionRadius() const;

	const bool GetIsMove() const;

	const bool GetIsGround() const;

	const bool GetIsDash() const;

	const bool GetIsStop() const;

	const VECTOR GetDirection()const;

	const VECTOR GetInputDir() const;



private:

	

	std::shared_ptr<RigidBody> rigid_body_;
	std::shared_ptr<const InputBase> input_;
	std::shared_ptr<CheckMyArea> my_area_;
	std::shared_ptr<SkillBase> skill_;
	std::shared_ptr<SkillBase> second_skill_;
	std::shared_ptr<BehaviorBase> test_behavior_;
	std::shared_ptr<SkillBase> avoid_;

	VECTOR* camera_dir_;
	VECTOR right_hand_pos_;
	VECTOR left_hand_pos_;
	VECTOR head_pos_;

	VECTOR attack_target_pos_;

	std::string name_;
	int skill1_id_;
	int skill2_id_;

	float speed_;
	float target_rot_y_;
	float fall_speed_;

	float detection_radius_;

	bool is_move_;
	bool is_dash_;
	bool* is_punch_;
	bool is_stop_;
	bool is_attack_target_in_range_;		// çUåÇëŒè€Ç™îÕàÕì‡Ç…Ç¢ÇÈÇÃÇ©

	// ä÷êîåQ

	void LoadFile(const char* file_path, const std::string my_name);

	void MakeSkill(std::weak_ptr<Player> owner);

	void Move();

	void Gravity();

	void UpdateBone();

	void DecideAttackTarget();

};
