#pragma once
#include"collider_base.h"

class Capsule : public ColliderBase
{
public:

	Capsule(float r,float vertical);

	~Capsule() override;

	void Draw(const VECTOR& pos) override;

private:

	float r_;
	float vertical_;

};