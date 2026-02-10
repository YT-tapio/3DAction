#pragma once
#include"collider_base.h"

struct Contact;

class Capsule : public ColliderBase
{
public:

	Capsule(float r,float vertical,VECTOR offset_vel);

	~Capsule() override;

	void Draw(const VECTOR& pos) override;

	bool CheckCollision(const VECTOR& my_pos, const VECTOR& vel,const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact) override;

	void FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact) override;

	const float GetRadius() const;

	const float GetVertical() const;

	const VECTOR GetOffsetVel() const;

private:

	float r_;
	float vertical_;

	VECTOR offset_vel_;

};