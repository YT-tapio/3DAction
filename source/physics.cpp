#include<iostream>
#include"DxLib.h"
#include"physics.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"vector_assistant.h"

void Physics::AddBody(std::shared_ptr<RigidBody> body)
{
	rigid_bodies_.push_back(body);
}

void Physics::Update()
{
	// –€ŽC‚Ì“K‰ž
	Resistance();

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

	//’…’n”»’è
	CheckGround();
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

void Physics::Resistance()
{
	// –€ŽC“™‚Ì’ïR‚Ì“K‰ž“K‰ž
	for (auto& body : rigid_bodies_)
	{
		// “K‰ž‚ðŽó‚¯‚È‚¢‚à‚Ì
		if (!body->GetIsKinematic()) { continue; }

		// “®‚¢‚Ä‚¢‚È‚¢
		if (!body->IsMove()) { continue; }

		VECTOR offset_vel = VectorAssistant::VGetZero();

		//‘S‘Ì‚ÌˆÚ“®—Ê
		VECTOR vel = VAdd(VectorAssistant::VGetFlat(body->GetVelocity()), VectorAssistant::VGetFlat(body->GetBeforeVelocity()));

		// offset_vel‚Ì‹t‚ÌƒxƒNƒgƒ‹‚ð³‹K‰»‚µA’ïR‚Ì‹­‚³‚ð‚©‚¯‚é
		VECTOR resistance_vel = VScale(VNorm(VectorAssistant::VGetReverce(vel)), kResistanceNum);
		// offset_vel‚É‘«‚·
		offset_vel = VAdd(offset_vel, resistance_vel);
		//‚»‚µ‚Ä‚à‚Æ‚à‚Æ‚Ìy‚ÌˆÚ“®—Ê‚É‚·‚é
		offset_vel.y = body->GetVelocity().y;

		body->Update(offset_vel);
	}
}

void Physics::CheckGround()
{
	// ’…’n‚Ì”»’è
	for (auto& main_body : rigid_bodies_)
	{
		if (!main_body->GetUseGravity()) { continue; }

		for (auto& target_body : rigid_bodies_)
		{

		}
	}

}