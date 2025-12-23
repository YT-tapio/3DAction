#include<iostream>
#include"DxLib.h"
#include"physics.h"
#include"rigid_body.h"

void Physics::AddBody(std::shared_ptr<RigidBody> body)
{
	rigid_bodies_.push_back(body);
}

void Physics::Update()
{
	for (auto& main_body : rigid_bodies_)
	{
		for (auto& target_body : rigid_bodies_)
		{
			if (main_body == target_body) { continue; }

			if (CheckHit(main_body, target_body))
			{
				main_body->OnHit(target_body->GetIHitObject());
				target_body->OnHit(main_body->GetIHitObject());
				FixPos(main_body, target_body);
			}

		}

	}

}

bool Physics::CheckHit(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other)
{


	return FALSE;
}

void Physics::FixPos(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other)
{




}