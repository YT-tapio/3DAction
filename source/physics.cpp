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
#include"lerp.h"
#include"debug.h"
#include"check_my_area.h"
#include"FPS.h"

void Physics::AddBody(std::shared_ptr<RigidBody> body)
{
	rigid_bodies_.push_back(body);
}

void Physics::Debug()
{
	int i = 0;
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "---normal---", GetColor(255, 255, 255));
	Debug::GetInstance().Add();
	for (const auto& poly : contact.polys)
	{ 
		i++;
		VECTOR center_pos = VectorAssistant::VDevide(VAdd(VAdd(poly.position[0], poly.position[1]), poly.position[2]), 3);
		DrawTriangle3D(poly.position[0], poly.position[1], poly.position[2], GetColor(255, 0, 0), FALSE);
		DrawLine3D(center_pos, VAdd(center_pos, VScale(poly.normal, 2)), GetColor(255, 255, 255));
		VECTOR kVertical = VGet(0.f, 1.f, 0.f);
		const float kWallRad = RadianAssistant::kOneRad * 80.f;

		// 法線で決める
		float rad = VectorAssistant::GetTwoVectorRad(kVertical, poly.normal);

		DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), GetColor(255, 255, 255), "%d", i);
		Debug::GetInstance().Add();
		Debug::GetInstance().DrawVector(center_pos);
		Debug::GetInstance().DrawVector(poly.normal);
		DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), GetColor(255, 255, 255), "%.2f", rad);
		Debug::GetInstance().Add();
	}
}

void Physics::Update()
{
	// 地上の投影
	GroundProj();

	// 摩擦の適応
	Resistance();

	//printfDx("-----------------\n");

	for (auto& main_body : rigid_bodies_)
	{
		if (!main_body->GetIsActive()) { continue; }
		for (auto& target_body : rigid_bodies_)
		{
			if (!target_body->GetIsActive()) { continue; }
			if (main_body == target_body) { continue; }
			contact.polys.clear();
			// コライダーにhitの確認を行う
			auto my_coll		= main_body->GetCollider();
			auto target_coll	= target_body->GetCollider();
			if (my_coll->CheckCollision(main_body->GetPosition(),main_body->GetVelocity(), target_body->GetPosition(),target_body->GetVelocity(),target_coll, contact))
			{
				
				main_body->OnHit(target_body->GetIPhysicsObject());
				target_body->OnHit(main_body->GetIPhysicsObject());

				if (main_body->GetIsKinematic()) { continue; }

				// 押し戻し
				VECTOR offset_vel = my_coll->FixPos(main_body->GetPosition(), main_body->GetVelocity(), target_body->GetVelocity(), target_coll, contact);
				main_body->Update(offset_vel);
			}
			else
			{
				main_body->UnHit(target_body->GetIPhysicsObject());
				target_body->UnHit(main_body->GetIPhysicsObject());
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

bool Physics::CheckHitGroundProj(std::shared_ptr<RigidBody>other, Contact& contact, const VECTOR& segment_start_pos, const float& ground_proj_length)
{
	bool is_hit = FALSE;

	VECTOR segment_end_pos = VAdd(segment_start_pos, VGet(0.f, ground_proj_length, 0.f));
	std::shared_ptr<ColliderBase> other_collider = other->GetCollider();

	switch (other_collider->GetName())
	{	
	case ColliderName::kAABB:
	{

		break;
	}
	case ColliderName::kOBB:
	{

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
		VECTOR capsule_start_pos = VAdd(other->GetPosition(), capsule->GetOffsetVel());
		VECTOR capsule_end_pos = VAdd(capsule_start_pos, VGet(0.f, capsule->GetVertical(), 0.f));
		is_hit = Collision::SegmentToCapsule(segment_start_pos, segment_end_pos, capsule_start_pos, capsule_end_pos, capsule->GetRadius());// その型とセグメントの当たり判定を行う
		
		break;
	}
	case ColliderName::kMesh:
	{
		// 型変換をする
		auto mesh = dynamic_cast<Mesh*>(other_collider.get());
		is_hit = Collision::SegmentToMesh(segment_start_pos, segment_end_pos, mesh->GetHandle(), contact);// その型とセグメントの当たり判定を行う
		break;
	}
	default:
		printfDx("範囲外が参照されています\n");
		break;
	}

	return is_hit;
}

bool Physics::CheckHitFoot(std::shared_ptr<RigidBody> me, std::shared_ptr<RigidBody> other,Contact& contact,const float& ground_proj_length)
{
	bool is_hit = FALSE;
	VECTOR offset_proj = me->GetVelocity();	// 投影するもの
	// meのposから足元にレイを飛ばして他のものと当たっているのかを検知する
	// 線分とotherとの当たり判定を行う
	
	// meから真下に線分を伸ばす
	VECTOR segment_start_pos = me->GetPosition();
	VECTOR segment_end_pos		= VAdd(segment_start_pos, VGet(0.f, -kGroundProjLength, 0.f));

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
		is_hit = Collision::SegmentToMesh(segment_start_pos, segment_end_pos, mesh->GetHandle(),contact);// その型とセグメントの当たり判定を行う
		
		if (is_hit)
		{
			offset_proj = VAdd(offset_proj,Resolve::SegmentMesh(segment_start_pos, segment_end_pos, mesh->GetHandle(), contact));
		}
		
		break;
	}
	default:
		printfDx("範囲外が参照されています。\n");
		break;
	}

	me->Update(offset_proj);

	return is_hit;
}

void Physics::GroundProj()
{
	// 坂の投影を行います
	for (auto& main_body : rigid_bodies_)
	{
		// アクティブ状態じゃない、ボーンによる影響しか受けない場合をのぞく
		if (!main_body->GetIsActive()) { continue; }
		if (VSize(main_body->GetVelocity()) == 0.f) { continue; }
		if (main_body->GetIsKinematic()) { continue; }

		Contact ground_contact = {};

		VECTOR offset_proj_vec = main_body->GetVelocity();
		VECTOR body_old_pos = main_body->GetPosition();		// 移動前のpos
		VECTOR body_future_pos = VAdd(body_old_pos, offset_proj_vec); // 移動後のpos
		VECTOR body_old_segment_end_pos = VAdd(body_old_pos, VGet(0.f, -kGroundProjLength, 0.f));	//移動前のposから真下にセグメントを伸ばす
		bool is_hit_old = FALSE;

		for (auto& target_body : rigid_bodies_)
		{
			// 同じものは除外
			if (target_body == main_body) { continue; }
			// ここで昔のposが当たっているのかをcheckする
			if (!CheckHitGroundProj(target_body, ground_contact, body_old_pos, -kGroundProjLength)) { continue; }
			// 未来のやつを判断する
			const float kOffsetProjLength = kGroundProjLength * 2.f;
			bool is_hit_future = CheckHitFoot(main_body, target_body, ground_contact, kOffsetProjLength);
		}
		if (!is_hit_old) { continue; }
	}
	
	
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

		VECTOR now_flat_vel		= VectorAssistant::VGetFlat(body->GetVelocity());
		VECTOR target_flat_vel	= VectorAssistant::VGetFlat(body->GetTargetVelocity());
		float target_y = body->GetTargetVelocity().y;
		float friction = body->GetFriction() * FPS::GetInstance().GetDeltaTime() * 60.f;
		VECTOR vel = Lerp::DampV(now_flat_vel, target_flat_vel,friction);
		vel = VAdd(vel, VGet(0.f, target_y, 0.f));
		body->SetVelocity(vel);
	}
}

void Physics::CheckGround()
{
	// 着地の判定
	for (auto& main_body : rigid_bodies_)
	{
		if (!main_body->GetUseGravity()) { continue; }
		
		auto area = std::dynamic_pointer_cast<CheckMyArea>(main_body->GetIPhysicsObject());
		if (area != nullptr) { continue; }
		for (auto& target_body : rigid_bodies_)
		{
			if (!target_body->GetIsActive()) { continue; }
			if (main_body == target_body) { continue; }

			auto target_area = std::dynamic_pointer_cast<CheckMyArea>(target_body->GetIPhysicsObject());
			if (target_area != nullptr) 
			{ 
				continue;
			}

			Contact contact = {};
			// IPhysicsの足元当たり判定を呼びたい
			auto body = main_body->GetIPhysicsObject().get();

			// rigid_body内の足元検知用のレイと周りのオブジェクトとの当たり判定を行う
			if (CheckHitFoot(main_body, target_body,contact,kGroundProjLength))
			{
				body->OnGrounded(target_body->GetIPhysicsObject());
				break;
			}
			else
			{
				body->OnUnGrounded(target_body->GetIPhysicsObject());
			}
		}
	}

}