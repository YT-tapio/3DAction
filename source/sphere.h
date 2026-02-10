#pragma once
#include"collider_base.h"

struct Contact;

class Sphere : public ColliderBase
{
public:

	Sphere(float r, VECTOR offset_vel);

	~Sphere() override;

	bool CheckCollision(const VECTOR& my_pos, const VECTOR& vel,const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll,Contact& contact) override;

	VECTOR FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact) override;

	void Draw(const VECTOR& pos) override;

	const float GetRadius() const;

	const VECTOR GetOffsetVel() const;

private:

	float r_;

	VECTOR offset_vel_;
};
