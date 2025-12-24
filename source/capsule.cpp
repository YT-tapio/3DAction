#include"DxLib.h"
#include"capsule.h"
#include"color.h"


Capsule::Capsule(float r,float vertical,VECTOR offset_vel)
	: ColliderBase(ColliderName::kCapsule)
	, r_(r)
	, vertical_(vertical)
	, offset_vel_(offset_vel)
{

}

Capsule::~Capsule()
{

}

void Capsule::Draw(const VECTOR& pos)
{
	VECTOR start = VAdd(pos, VGet(0.f, r_, 0.f));
	VECTOR end = VAdd(start, VGet(0.f, vertical_, 0.f));

	const int kDivNum = 20;

	DrawCapsule3D(start, end, r_, kDivNum, Color::kWhite, Color::kWhite, FALSE);
}

const float Capsule::GetRadius() const
{
	return r_;
}

const float Capsule::GetVertical() const
{
	return vertical_;
}

const VECTOR Capsule::GetOffsetVel() const
{
	return offset_vel_;
}