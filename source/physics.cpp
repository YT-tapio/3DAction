#include<iostream>
#include"DxLib.h"
#include"physics.h"
#include"rigid_body.h"
#include"collider_base.h"

void Physics::AddBody(std::shared_ptr<RigidBody> body)
{
	rigid_bodies_.push_back(body);
}

void Physics::Update()
{
	for (auto& main_body : rigid_bodies_)
	{
		// “®‚¢‚Ä‚¢‚È‚¢‚à‚Ì‚Í’¼‚®‚É•Ê‚Ì‚à‚Ì‚É
		if (VSize(main_body->GetVelocity()) == 0.f) { continue; }

		for (auto& target_body : rigid_bodies_)
		{
			if (main_body == target_body) { continue; }

			if (CheckHit(main_body, target_body))
			{
				main_body->OnHit(target_body->GetIPhysicsObject());
				target_body->OnHit(main_body->GetIPhysicsObject());
				FixPos(main_body, target_body);
			}
		}
	}

	// ’…’n‚Ì”»’è
	for (auto& main_body : rigid_bodies_)
	{
		if (!main_body->GetUseGravity()) { continue; }

		for (auto& target_body : rigid_bodies_)
		{

		}
	}

}

bool Physics::CheckHit(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other)
{
	//“–‚½‚Á‚Ä‚¢‚é‚©‚Ì”»•Ê‚ðs‚¢‚Ü‚·

	// collider‚ÌŽæ“¾
	auto me_coll			= me->GetCollider();
	auto other_coll		= other->GetCollider();

	auto me_name			= me_coll->GetName();

	switch (me_name)
	{
	case ColliderName::kSphere:
		return TRUE;
		break;

	case ColliderName::kCapsule:
		return TRUE;
		break;

	case ColliderName::kAABB:
		return TRUE;
		break;

	case ColliderName::kOBB:
		return TRUE;
		break;

	case ColliderName::kMesh:
		return TRUE;
		break;
	}


	return FALSE;
}



void Physics::FixPos(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other)
{
	
}