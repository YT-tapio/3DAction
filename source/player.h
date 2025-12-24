#pragma once
#include"character_base.h"
#include"physics_interface.h"

class RigidBody;

class Player : public CharacterBase , public IPhysicsEventReceiver
{
public:

	Player(VECTOR* camera_dir);

	~Player() override;

	void Init() override;

	void Update() override;
	
	void Draw() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> obj) override;

	void OnGrounded() override;

	void OnUnGrounded() override;

private:



	const float kSpeed = 0.5f;

	std::shared_ptr<RigidBody> rigid_body_;

	VECTOR dir_;
	VECTOR vel_;


	VECTOR* camera_dir_;



	// ä÷êîåQ

	void LoadFile();

	void Move();

};
