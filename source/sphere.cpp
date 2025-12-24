#include"DxLib.h"
#include"sphere.h"
#include"color.h"


Sphere::Sphere(float r, VECTOR offset_vel)
	:ColliderBase(ColliderName::kSphere)
	, r_(r)
	, offset_vel_ (offset_vel)
{

}

Sphere::~Sphere()
{

}

void Sphere::Draw(const VECTOR& pos)
{
	const int kDivNum = 20;

	DrawSphere3D(pos, r_, kDivNum, Color::kWhite, Color::kWhite, FALSE);
}

const float Sphere::GetRadius() const
{
	return r_;
}

const VECTOR Sphere::GetOffsetVel() const
{
	return offset_vel_;
}
