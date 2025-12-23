#pragma once
#include"character_base.h"
#include"hit_interface.h"

class RigidBody;

class Player : public CharacterBase , public IHit
{
public:

	Player(VECTOR* camera_dir);

	~Player() override;

	void Init() override;

	void Update() override;
	
	void Draw() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IHit> obj) override;

private:



	const float kSpeed = 1.f;

	std::shared_ptr<RigidBody> rigid_body_;

	VECTOR dir_;
	VECTOR vel_;


	VECTOR* camera_dir_;



	// ä÷êîåR

	void LoadFile();

	void Move();

};
