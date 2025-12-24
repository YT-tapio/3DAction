#pragma once
#include"collider_base.h"

class Sphere : public ColliderBase
{
public:

	Sphere(float r, VECTOR offset_vel);

	~Sphere() override;

	void Draw(const VECTOR& pos) override;

	const float GetRadius() const;

	const VECTOR GetOffsetVel() const;

private:

	float r_;

	VECTOR offset_vel_;
};
