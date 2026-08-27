#include"DxLib.h"
#include"capsule.h"
#include"color.h"
#include"collider_name.h"
#include"sphere.h"
#include"mesh.h"
#include"contact.h"
#include"collision.h"
#include"resolve.h"

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
	VECTOR start = VAdd(VAdd(pos, offset_vel_), VGet(0.f, r_, 0.f));
	VECTOR end = VAdd(start, VGet(0.f, vertical_, 0.f));

	const int kDivNum = 20;

	DrawCapsule3D(start, end, r_, kDivNum, Color::kWhite, Color::kWhite, FALSE);
}

bool Capsule::CheckCollision(const VECTOR& my_pos, const VECTOR& vel,const VECTOR& other_pos, const VECTOR& other_vel,std::shared_ptr<ColliderBase> other_coll,Contact& contact)
{

	bool is_hit = FALSE;

	VECTOR start_pos	= VAdd(my_pos,		VGet(0.f, r_, 0.f));
	VECTOR end_pos		= VAdd(start_pos, VGet(0.f, vertical_, 0.f));

	// collider‚ÌƒLƒƒƒbƒVƒ…‚ğs‚¤
	switch (other_coll->GetName())
	{
	case ColliderName::kAABB:
	{
		// Œ^•ÏŠ·
		// auto aabb = std::dynamic_pointer_cast<AABB>(other_coll);
	}
		break;
	case ColliderName::kOBB:
	{
		// Œ^•ÏŠ·
		// auto obb = std::dynamic_pointer_cast<OBB>(other_coll);
	}
		break;
	case ColliderName::kSphere:
	{
		// Œ^•ÏŠ·
		auto sphere = std::dynamic_pointer_cast<Sphere>(other_coll);
		//is_hit = Collision::CapsuleToCapsule(other_pos, VAdd(other_pos, VGet(0.f, 0.01f, 0.f)), sphere->GetRadius(), start_pos, end_pos, r_);
		//is_hit = Collision::IsMoveSphereToCapsule(other_pos, sphere->GetRadius(), other_vel, start_pos, end_pos, r_, vel);
		is_hit = Collision::SphereToSphere(other_pos, sphere->GetRadius(), start_pos, r_);
		//is_hit = Collision::SphereToCapsule(other_pos, sphere->GetRadius(), start_pos, end_pos, r_);
	}
		break;
	case ColliderName::kCapsule:
	{
		// Œ^•ÏŠ·
		auto capsule = std::dynamic_pointer_cast<Capsule>(other_coll);
		float other_radius = capsule->GetRadius();
		float other_vertical = capsule->GetVertical();
		
		
		VECTOR other_coll_start_pos = VAdd(other_pos, VGet(0.f, other_radius, 0.f));
		VECTOR other_coll_end_pos = VAdd(other_coll_start_pos, VGet(0.f, other_vertical, 0.f));
		is_hit = Collision::IsMoveCapsuleToCapsule(start_pos, end_pos, r_, vel,other_coll_start_pos, other_coll_end_pos, other_radius,other_vel);

	}
		break;
	case ColliderName::kMesh:
	{
		// Œ^•ÏŠ·
		auto mesh = std::dynamic_pointer_cast<Mesh>(other_coll);
		
		is_hit = Collision::IsMoveCapsuleToMesh(start_pos, end_pos, vel, r_, mesh->GetHandle(), contact);
	}
		break;

	default:
		printfDx("”ÍˆÍŠO‚ğQÆ‚µ‚Ä‚¢‚Ü‚·\n");
		break;
	}


	return is_hit;
}

VECTOR Capsule::FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact)
{
	if (VSize(vel) == 0.f) { return vel; }
	VECTOR start_pos = VAdd(my_pos, VGet(0.f, r_, 0.f));
	VECTOR end_pos = VAdd(start_pos, VGet(0.f, vertical_, 0.f));

	VECTOR offset_vel = vel;

	// collider‚ÌƒLƒƒƒbƒVƒ…‚ğs‚¤

	switch (other_coll->GetName())
	{
	case ColliderName::kAABB:
	{
		// Œ^•ÏŠ·
		// auto aabb = std::dynamic_pointer_cast<AABB>(other_coll);
	}
	break;
	case ColliderName::kOBB:
	{
		// Œ^•ÏŠ·
		// auto obb = std::dynamic_pointer_cast<OBB>(other_coll);
	}
	break;
	case ColliderName::kSphere:
	{
		// Œ^•ÏŠ·
		auto sphere = std::dynamic_pointer_cast<Sphere>(other_coll);

	}
	break;
	case ColliderName::kCapsule:
	{
		// Œ^•ÏŠ·
		auto capsule = std::dynamic_pointer_cast<Capsule>(other_coll);
		VECTOR other_start_pos = VAdd(other_pos, VGet(0.f, capsule->GetRadius(), 0.f));
		VECTOR other_end_pos = VAdd(other_start_pos, VGet(0.f, capsule->GetVertical(), 0.f));
		offset_vel = Resolve::CapsuleCapsule(start_pos, end_pos, r_, vel, other_start_pos, other_end_pos, capsule->GetRadius());
		//offset_vel = VectorAssistant::VGetZero();
	}
	break;
	case ColliderName::kMesh:
	{
		//printfDx("wow");
		// Œ^•ÏŠ·
		auto mesh = std::dynamic_pointer_cast<Mesh>(other_coll);
		// ©•ª‚ª“®‚¢‚Ä‚¢‚é‚©‚Ì”»’f‚ğ‚·‚é
		offset_vel = Resolve::CapsuleMesh(start_pos, end_pos, r_, vel, mesh->GetHandle(), contact);
	}
	break;

	default:
		printfDx("”ÍˆÍŠO‚ğQÆ‚µ‚Ä‚¢‚Ü‚·\n");
		break;
	}

	return offset_vel;
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