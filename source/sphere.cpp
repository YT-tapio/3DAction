#include"DxLib.h"
#include"sphere.h"
#include"color.h"
#include"collider_name.h"
#include"vector_assistant.h"

Sphere::Sphere(float r, VECTOR offset_vel)
	:ColliderBase(ColliderName::kSphere)
	, r_(r)
	, offset_vel_ (offset_vel)
{

}

Sphere::~Sphere()
{

}

bool Sphere::CheckCollision(const VECTOR& my_pos, const VECTOR& vel,const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll,Contact& contact)
{
	bool is_hit = FALSE;

	return is_hit;
}

VECTOR Sphere::FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact)
{
	return VectorAssistant::VGetZero();
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
