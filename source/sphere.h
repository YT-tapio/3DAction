#pragma once
#include"collider_base.h"

class Sphere : public ColliderBase
{
public:

	Sphere(float r);

	~Sphere() override;

	void Draw(const VECTOR& pos) override;

private:

	float r_;


};
