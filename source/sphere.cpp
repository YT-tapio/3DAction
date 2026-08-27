#include"DxLib.h"
#include"sphere.h"
#include"color.h"
#include"collider_name.h"
#include"collision.h"
#include"vector_assistant.h"
#include"capsule.h"
#include"mesh.h"
#include"resolve.h"

Sphere::Sphere(float r, VECTOR offset_vel)
	:ColliderBase(ColliderName::kSphere)
	, r_(r)
	, offset_vel_ (offset_vel)
{

}

Sphere::~Sphere()
{

}

bool Sphere::CheckCollision(const VECTOR& my_pos, const VECTOR& vel,const VECTOR& other_pos, const VECTOR& other_vel, std::shared_ptr<ColliderBase> other_coll,Contact& contact)
{
	bool is_hit = FALSE;
	//VECTOR center_pos = VAdd(my_pos, VGet(0.f, r_, 0.f));
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
		
		is_hit = Collision::IsMoveSphereToSphere(my_pos, r_, vel, other_pos, sphere->GetRadius(), other_vel);
	}
	break;
	case ColliderName::kCapsule:
	{
		// Œ^•ÏŠ·
		auto capsule = std::dynamic_pointer_cast<Capsule>(other_coll);
		float capsule_radius = capsule->GetRadius();
		float capsule_vertical = capsule->GetVertical();
		//VECTOR capsule_start_pos = other_pos;
		VECTOR capsule_start_pos = VAdd(other_pos, VGet(0.f, capsule_radius, 0.f));
		VECTOR capsule_end_pos = VAdd(capsule_start_pos, VGet(0.f, capsule_vertical, 0.f));
		//is_hit = Collision::CapsuleToCapsule(center_pos, VAdd(center_pos, VGet(0.f, 0.01f, 0.f)), r_, capsule_start_pos, capsule_end_pos, capsule_radius);
		//is_hit = Collision::SphereToSphere(my_pos, r_, capsule_start_pos, capsule_radius);
		//is_hit = Collision::SphereToCapsule(center_pos, r_, capsule_start_pos, capsule_end_pos, capsule_radius);
		is_hit = Collision::IsMoveSphereToCapsule(my_pos, r_, vel, capsule_start_pos, capsule_end_pos, capsule_radius, other_vel);
	}
	break;
	case ColliderName::kMesh:
	{
		// Œ^•ÏŠ·
		auto mesh = std::dynamic_pointer_cast<Mesh>(other_coll);

		is_hit = Collision::IsMoveSphereToMesh(my_pos, vel, r_, mesh->GetHandle(), contact);
	}
	break;

	default:
		printfDx("”ÍˆÍŠO‚ğQÆ‚µ‚Ä‚¢‚Ü‚·\n");
		break;
	}


	return is_hit;
}

VECTOR Sphere::FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact)
{
	VECTOR offset_vel				= vel;
	VECTOR old_center_pos		= VAdd(my_pos, VGet(0.f, r_, 0.f));	// ˆÚ“®‘O‚Ì’†S“_
	VECTOR next_center_pos	= VAdd(old_center_pos,vel);				// ˆÚ“®Œã‚Ì’†S“_

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
	}
	break;
	case ColliderName::kMesh:
	{
		//printfDx("wow");
		// Œ^•ÏŠ·
		auto mesh = std::dynamic_pointer_cast<Mesh>(other_coll);
		// ©•ª‚ª“®‚¢‚Ä‚¢‚é‚©‚Ì”»’f‚ğ‚·‚é
		offset_vel = Resolve::SphereMesh(old_center_pos, r_, vel, mesh->GetHandle(), contact);
	}
	break;

	default:
		printfDx("”ÍˆÍŠO‚ğQÆ‚µ‚Ä‚¢‚Ü‚·\n");
		break;
	}

	return offset_vel;
}

void Sphere::Draw(const VECTOR& pos)
{
	const int kDivNum = 20;

	VECTOR center_pos = VAdd(pos,offset_vel_);

	DrawSphere3D(center_pos, r_, kDivNum, Color::kWhite, Color::kWhite, FALSE);
}

const float Sphere::GetRadius() const
{
	return r_;
}

const VECTOR Sphere::GetOffsetVel() const
{
	return offset_vel_;
}
