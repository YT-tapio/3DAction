#include<iostream>
#include"DxLib.h"
#include"physics.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"vector_assistant.h"
#include"collider_name.h"
#include"collision.h"
void Physics::AddBody(std::shared_ptr<RigidBody> body)
{
	rigid_bodies_.push_back(body);
}

void Physics::Update()
{
	// 摩擦の適応
	Resistance();

	for (auto& main_body : rigid_bodies_)
	{
		// 動いていないものは直ぐに別のものに
		if (VSize(main_body->GetVelocity()) == 0.f) { continue; }

		for (auto& target_body : rigid_bodies_)
		{
			if (main_body == target_body) { continue; }

			if (CheckHit(main_body, target_body))
			{
				main_body->OnHit(target_body->GetIPhysicsObject());
				target_body->OnHit(main_body->GetIPhysicsObject());

				if (main_body->GetIsKinematic()) { continue; }

				// 押し戻し
				FixPos(main_body, target_body);
			}

		}

		main_body->SetPos();

	}

	//着地判定
	CheckGround();
}

bool Physics::CheckHit(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other)
{
	//当たっているかの判別を行います

	// colliderの取得
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

bool Physics::CheckHitFoot(std::shared_ptr<RigidBody> me, std::shared_ptr<RigidBody> other)
{
	// meのposから足元にレイを飛ばして他のものと当たっているのかを検知する
	// 線分とotherとの当たり判定を行う
	
	// meから真下に線分を伸ばす
	VECTOR segment_end_pos = VAdd(me->GetPosition(), VGet(0.f, -1.f, 0.f));

	// そのrigidbodyが何のコライダーを持っているかの判別をする

	auto other_collider = other->GetCollider();

	switch (other_collider->GetName())
	{
	case ColliderName::kMesh:

		//Collision::SegmentToMesh();

		break;


	default:

	}


	return FALSE;
}



void Physics::FixPos(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other)
{
	
}

void Physics::Resistance()
{
	// 摩擦等の抵抗の適応適応
	for (auto& body : rigid_bodies_)
	{

		// 適応を受けないもの
		if (body->GetIsKinematic()) { continue; }
		// 動いていない
		if (!body->IsMove()) { continue; }

		// 最大値はrigidbodyにある
		float max_speed = body->GetMaxSpeed();


		VECTOR offset_vel = VectorAssistant::VGetZero();
		// 全体の移動量
		VECTOR vel = VAdd(VectorAssistant::VGetFlat(body->GetVelocity()), VectorAssistant::VGetFlat(body->GetBeforeVelocity()));
		// velの逆のベクトルを正規化し、抵抗の強さをかける
		VECTOR resistance_vel = VScale(VectorAssistant::VGetReverce(VNorm(vel)), kResistanceNum);

		// 最大の移動量
		//offset_vel = VectorAssistant::VMaxf(offset_vel, VSize(VectorAssistant::VGetFlat(body->GetVelocity())));
		// velに足す
		offset_vel = VAdd(vel, resistance_vel);
		// 摩擦によって方向が変わらないよう調整する
		// 向きが一緒かどうか
		// 自分の入力がゼロの時
		if (VectorAssistant::IsSameDir(offset_vel, resistance_vel))
		{
			offset_vel = VectorAssistant::VGetZero();
		}

		if (VSize(body->GetVelocity()) > 0)
		{
			offset_vel = VectorAssistant::VMaxf(offset_vel, max_speed);
		}

		// そしてもともとのyの移動量にする
		offset_vel.y = body->GetVelocity().y;

		body->Update(offset_vel);
		
	}
}

void Physics::CheckGround()
{
	// 着地の判定
	for (auto& main_body : rigid_bodies_)
	{
		if (!main_body->GetUseGravity()) { continue; }

		for (auto& target_body : rigid_bodies_)
		{
			// rigid_body内の足元検知用のレイと周りのオブジェクトとの当たり判定を行う
			if (CheckHitFoot(main_body, target_body))
			{
				
			}
		}
	}

}