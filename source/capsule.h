#pragma once
#include"collider_base.h"

class Capsule : public ColliderBase
{
public:

	Capsule(float r,float vertical,VECTOR offset_vel);

	~Capsule() override;

	void Draw(const VECTOR& pos) override;

	const float GetRadius() const;

	const float GetVertical() const;

	const VECTOR GetOffsetVel() const;

private:

	float r_;
	float vertical_;

	VECTOR offset_vel_;

};