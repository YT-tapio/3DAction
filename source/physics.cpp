#include<iostream>
#include"DxLib.h"
#include"physics.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"vector_assistant.h"
#include"collider_name.h"
#include"collision.h"
#include"mesh.h"
#include"physics_interface.h"
#include"resolve.h"
#include"contact.h"

void Physics::AddBody(std::shared_ptr<RigidBody> body)
{
	rigid_bodies_.push_back(body);
}

void Physics::Update()
{
	// 摩擦の適応
	// Resistance();

	for (auto& main_body : rigid_bodies_)
	{
		// 動いていないものは直ぐに別のものに
		if (VSize(main_body->GetVelocity()) == 0.f) { continue; }

		for (auto& target_body : rigid_bodies_)
		{
			if (main_body == target_body) { continue; }
			Contact contact{};
			// コライダーにhitの確認を行う
			auto my_coll		= main_body->GetCollider();
			auto target_coll	= target_body->GetCollider();
			if (my_coll->CheckCollision(main_body->GetPosition(),main_body->GetVelocity(), target_body->GetPosition(),target_coll, contact))
			{
				main_body->OnHit(target_body->GetIPhysicsObject());
				target_body->OnHit(main_body->GetIPhysicsObject());

				if (main_body->GetIsKinematic()) { continue; }

				// 押し戻し
				VECTOR offset_vel = my_coll->FixPos(main_body->GetPosition(), main_body->GetVelocity(), target_body->GetVelocity(), target_coll, contact);

				main_body->Update(offset_vel);

			}

			MV1CollResultPolyDimTerminate(contact.hit_dim);
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
		return FALSE;
		break;

	case ColliderName::kCapsule:
		return FALSE;
		break;

	case ColliderName::kAABB:
		return FALSE;
		break;

	case ColliderName::kOBB:
		return FALSE;
		break;

	case ColliderName::kMesh:
		return FALSE;
		break;
	}


	return FALSE;
}

bool Physics::CheckHitFoot(std::shared_ptr<RigidBody> me, std::shared_ptr<RigidBody> other)
{
	bool is_hit = FALSE;
	// meのposから足元にレイを飛ばして他のものと当たっているのかを検知する
	// 線分とotherとの当たり判定を行う
	
	// meから真下に線分を伸ばす
	VECTOR segment_start_pos	= me->GetPosition();
	VECTOR segment_end_pos		= VAdd(me->GetPosition(), VGet(0.f, -1.f, 0.f));

	// そのrigidbodyが何のコライダーを持っているかの判別をする

	std::shared_ptr<ColliderBase> other_collider = other->GetCollider();

	switch (other_collider->GetName())
	{
	case ColliderName::kAABB:
	{
		/*
		// 型変換をする
		auto mesh = dynamic_cast<*>(other_collider.get());
		is_hit = Collision::SegmentToMesh(segment_start_pos, segment_end_pos, mesh->GetHandle());// その型とセグメントの当たり判定を行う
		*/
		break;
	}
	case ColliderName::kOBB:
	{
		/*
		// 型変換をする
		auto mesh = dynamic_cast<Mesh*>(other_collider.get());
		is_hit = Collision::SegmentToMesh(segment_start_pos, segment_end_pos, mesh->GetHandle());// その型とセグメントの当たり判定を行う
		*/
		break;
	}
	case ColliderName::kSphere:
	{
		// 型変換をする
		auto sphere = dynamic_cast<Sphere*>(other_collider.get());
		VECTOR center_pos = other->GetPosition();
		is_hit = Collision::SegmentToSphere(segment_start_pos, segment_end_pos, center_pos, sphere->GetRadius());// その型とセグメントの当たり判定を行う
		break;
	}
	case ColliderName::kCapsule:
	{
		// 型変換をする
		auto capsule = dynamic_cast<Capsule*>(other_collider.get());
		VECTOR capsule_start_pos	= VAdd(other->GetPosition(), capsule->GetOffsetVel());
		VECTOR capsule_end_pos		= VAdd(capsule_start_pos, VGet(0.f, capsule->GetVertical(), 0.f));
		is_hit = Collision::SegmentToCapsule(segment_start_pos, segment_end_pos, capsule_start_pos, capsule_end_pos, capsule->GetRadius());// その型とセグメントの当たり判定を行う
		break;
	}
	case ColliderName::kMesh:
	{
		// 型変換をする
		auto mesh = dynamic_cast<Mesh*>(other_collider.get());
		is_hit = Collision::SegmentToMesh(segment_start_pos, segment_end_pos, mesh->GetHandle());// その型とセグメントの当たり判定を行う
		break;
	}
	default:
		printfDx("範囲外が参照されています。\n");
		break;

	}

	return is_hit;
}

void Physics::FixPos(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other)
{
	// 自分のcolliderが何かを取得

	auto my_collider		= me->GetCollider();
	auto other_collider		= other->GetCollider();

	switch (my_collider->GetName())
	{
	case ColliderName::kAABB:

		#pragma region 自分がAABBの当たり判定

		#pragma endregion
		break;

	case ColliderName::kOBB:

		#pragma region 自分がOBBの当たり判定

		#pragma endregion

		break;

	case ColliderName::kSphere:

#pragma region 自分がSphereの当たり判定
	{
		auto sphere = std::dynamic_pointer_cast<Sphere>(my_collider);	// sphereに変換
		SphereFixPos(sphere, other_collider);
	}
#pragma endregion
		break;

	case ColliderName::kCapsule:

#pragma region 自分がCapsuleの当たり判定
	{
		auto capsule = std::dynamic_pointer_cast<Capsule>(my_collider);
		CapsuleFixPos(capsule, other_collider);
	}
		#pragma endregion

		break;

	case ColliderName::kMesh:

		#pragma region 自分がmeshの当たり判定

		#pragma endregion

		break;

	default:
		printfDx("範囲外が参照されています\n");
		break;
	}


}

void Physics::SphereFixPos(std::shared_ptr<Sphere> me, std::shared_ptr<ColliderBase> other)
{

}

void Physics::CapsuleFixPos(std::shared_ptr<Capsule> me, std::shared_ptr<ColliderBase> other)
{
	// otherのキャストを行う

	switch (other->GetName())
	{
	case ColliderName::kAABB:
	{
		auto other_coll = std::dynamic_pointer_cast<Mesh>(other);
	}
		break;

	case ColliderName::kOBB:
	{
		auto other_coll = std::dynamic_pointer_cast<Mesh>(other);
	}
		break;

	case ColliderName::kSphere:
	{
		auto other_coll = std::dynamic_pointer_cast<Mesh>(other);
	}
		break;

	case ColliderName::kCapsule:
	{
		auto other_coll = std::dynamic_pointer_cast<Mesh>(other);
	}
		break;

	case ColliderName::kMesh:
	{
		auto other_coll = std::dynamic_pointer_cast<Mesh>(other);
	}
		break;

	default:
		printfDx("範囲外が参照されています\n");
		break;
	}


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

		body->SetVelocity(offset_vel);
		
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
			if (main_body == target_body) { continue; }

			// IPhysicsの足元当たり判定を呼びたい
			auto body = main_body->GetIPhysicsObject().get();

			// rigid_body内の足元検知用のレイと周りのオブジェクトとの当たり判定を行う
			if (CheckHitFoot(main_body, target_body))
			{
				body->OnGrounded();
			}
			else
			{
				body->OnUnGrounded();
			}
		}
	}

}