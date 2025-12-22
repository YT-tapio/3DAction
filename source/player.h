#pragma once
#include"character_base.h"

class RigidBody;

class Player : public CharacterBase
{
public:

	Player(VECTOR* camera_dir);

	~Player() override;

	void Init() override;

	void Update() override;
	
	void Draw() override;

	void Debug() override;

private:



	const float kSpeed = 1.f;

	std::shared_ptr<RigidBody> rigid_body_;

	VECTOR dir_;
	VECTOR vel_;


	VECTOR* camera_dir_;



	// ä÷êîåR

	void LoadFile();

	void Move();

	void OnHit(std::shared_ptr<ObjectBase> obj);

};
