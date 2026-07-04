#include<iostream>
#include<memory>
#include<string>
#include<unordered_map>
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

void Physics::Init()
{
	rigid_body_id_ = 0;
}

void Physics::AddBody(std::shared_ptr<RigidBody> body)
{
	// idのカウント
	rigid_body_id_++;

	// IDも一緒に振り分ける
	id_rigid_bodies_mp_[rigid_body_id_] = body;
}

void Physics::Debug()
{
	int i = 0;
	if (FALSE) { return; }
	
	
	for (const auto& pair : collisioned_pairs_id_)
	{
		DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), GetColor(0, 0, 0), "first - %d：second - %d", pair.first, pair.second);
		Debug::GetInstance().Add();
	}

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
	UpdateRigidBody();
	// 重力
	Gravity();
	// 地上の投影
	GroundProj();
	// 摩擦の適応
	Resistance();
	// 当たり判定と押し戻し
	Collision();
	//着地判定
	CheckGround();
}

void Physics::End()
{
	// 後始末
	rigid_body_id_ = 0;
	collisioned_pairs_id_.clear();
	id_rigid_bodies_mp_.clear();
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
		//is_hit = Collision::SegmentToSphere(segment_start_pos, segment_end_pos, center_pos, sphere->GetRadius());// その型とセグメントの当たり判定を行う
		break;
	}
	case ColliderName::kCapsule:
	{
		// 型変換をする
		auto capsule = dynamic_cast<Capsule*>(other_collider.get());
		VECTOR capsule_start_pos = VAdd(other->GetPosition(), capsule->GetOffsetVel());
		VECTOR capsule_end_pos = VAdd(capsule_start_pos, VGet(0.f, capsule->GetVertical(), 0.f));
		//is_hit = Collision::SegmentToCapsule(segment_start_pos, segment_end_pos, capsule_start_pos, capsule_end_pos, capsule->GetRadius());// その型とセグメントの当たり判定を行う
		
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
	
	// meを少しだけ上にし真下に線分を伸ばす
	VECTOR segment_start_pos = VAdd(me->GetPosition(),VGet(0.f,kOffsetCheckGround,0.f));
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

	me->UpdateVelocity(offset_proj);

	return is_hit;
}

void Physics::GroundProj()
{
	// 坂の投影を行います
	for (auto& id_main_body : id_rigid_bodies_mp_)
	{
		auto main_body = id_main_body.second;
		// アクティブ状態じゃない、ボーンによる影響しか受けない場合をのぞく
		if (!main_body->GetIsActive()) { continue; }
		if (VSize(main_body->GetVelocity()) == 0.f) { continue; }
		if (main_body->GetIsKinematic()) { continue; }
		if (main_body->IsStop()) { continue; }
		// if (main_body->GetFallSpeed() != 0.f) { continue; }
		// if (main_body->GetFallSpeed() != 0.f) { printfDx("a"); }
		
		Contact ground_contact = {};

		VECTOR offset_proj_vec = main_body->GetVelocity();
		VECTOR body_old_pos = main_body->GetPosition();		// 移動前のpos
		VECTOR body_future_pos = VAdd(body_old_pos, offset_proj_vec); // 移動後のpos
		VECTOR body_old_segment_end_pos = VAdd(body_old_pos, VGet(0.f, -kGroundProjLength, 0.f));	//移動前のposから真下にセグメントを伸ばす
		bool is_hit_old = FALSE;

		for (auto& target_id_body : id_rigid_bodies_mp_)
		{
			auto target_body = target_id_body.second;
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

void Physics::Resistance()
{
	// 摩擦等の抵抗の適応適応
	for (auto& id_rigid_body : id_rigid_bodies_mp_)
	{
		auto body = id_rigid_body.second;
		if (body->IsStop()) { continue; }
		// 適応を受けないもの
		if (body->GetIsKinematic()) { continue; }

		VECTOR now_flat_vel		= VectorAssistant::VGetFlat(body->GetVelocity());
		VECTOR target_flat_vel	= VectorAssistant::VGetFlat(body->GetTargetVelocity());
		float target_y = body->GetTargetVelocity().y;
		float friction = body->GetFriction();
		float delta_time = body->GetOwnerDeltaTime();
		VECTOR vel = Lerp::DampV(now_flat_vel, target_flat_vel, friction * delta_time);
		vel = VAdd(vel, VGet(0.f, target_y, 0.f));
		body->SetVelocity(vel);
	}
}

void Physics::UpdateRigidBody()
{
	for (auto& id_rigid_body : id_rigid_bodies_mp_)
	{
		auto body = id_rigid_body.second;
		body->Update();
	}
}

void Physics::Gravity()
{
	for (auto& main_body : id_rigid_bodies_mp_)
	{
		if (!main_body.second->IsStop())
		{
			main_body.second->AddForce();
		}
	}
}

void Physics::Collision()
{
	std::vector<std::pair<int, int>> current_collisioned_pairs_id;

	for (int i = 0; i < kLoopCollision; i++)
	{
		// 押し戻しされたか
		bool is_resolve = TRUE;

		for (auto& main_id_body : id_rigid_bodies_mp_)
		{
			auto main_id = main_id_body.first;
			auto main_body = main_id_body.second;
			if (!main_body->GetIsActive())
			{
				// 自分がactiveではないときはpairからなくす
				// 消去
				for (auto it = collisioned_pairs_id_.begin(); it != collisioned_pairs_id_.end();)
				{
					// first,secondどちらかに要素があるなら消去
					if (it->first == main_id || it->second == main_id)
					{
						it = collisioned_pairs_id_.erase(it);
					}
					else
					{
						++it;
					}
				}
				continue;
			}
			for (auto& target_id_body : id_rigid_bodies_mp_)
			{
				auto target_body = target_id_body.second;
				if (!target_body->GetIsActive()) { continue; }
				if (main_body == target_body) { continue; }
				contact.polys.clear();
				// コライダーにhitの確認を行う
				auto my_coll = main_body->GetCollider();
				auto target_coll = target_body->GetCollider();

				// idが低い方を先にする

				auto target_id = target_id_body.first;
				std::pair<int, int> pair;

				if (main_id < target_id)
				{
					pair = { main_id, target_id };
				}
				else
				{
					pair = { target_id,main_id };
				}

				if (my_coll->CheckCollision(main_body->GetPosition(), main_body->GetVelocity(), target_body->GetPosition(), target_body->GetVelocity(), target_coll, contact))
				{
					// 同じものがない場合はこの中であたったものを保存
					if (!CheckInPair(current_collisioned_pairs_id,pair))
					{
						// 中にないのならpiarを追加
						current_collisioned_pairs_id.emplace_back(pair);
					}


					if (main_body->GetIsKinematic()) { continue; }
					if (!target_body->IsObject()) { continue; }
					// 押し戻し
					VECTOR offset_vel = my_coll->FixPos(main_body->GetPosition(), main_body->GetVelocity(), target_body->GetPosition(), target_coll, contact);
					main_body->UpdateVelocity(offset_vel);
					is_resolve = TRUE;
				}
			}
		}

		if (!is_resolve)
		{
			break;
		}

	}

	// OnCollision系の処理をする
	// 今あたっているもの
	for (const auto& current_collisioned_pair : current_collisioned_pairs_id)
	{
		// 範囲内
		bool is_in_pair = FALSE;
		// 1フレーム前あたっていたもの
		for (const auto& collisioned_pair : collisioned_pairs_id_)
		{
			if (IsSamePair(collisioned_pair, current_collisioned_pair))
			{
				// 中にあるんだったらstay
				auto& first_rigid_body = id_rigid_bodies_mp_[current_collisioned_pair.first];
				auto& second_rigid_body = id_rigid_bodies_mp_[current_collisioned_pair.second];
				first_rigid_body->OnCollisionStay(second_rigid_body->GetIPhysicsObject());
				second_rigid_body->OnCollisionStay(first_rigid_body->GetIPhysicsObject());
				is_in_pair = TRUE;
				break;
			}
		}
		if (!is_in_pair)
		{
			// 中にないのならenter
			auto& first_rigid_body = id_rigid_bodies_mp_[current_collisioned_pair.first];
			auto& second_rigid_body = id_rigid_bodies_mp_[current_collisioned_pair.second];
			first_rigid_body->OnCollisionEnter(second_rigid_body->GetIPhysicsObject());
			second_rigid_body->OnCollisionEnter(first_rigid_body->GetIPhysicsObject());

			// 要素の追加
			collisioned_pairs_id_.emplace_back(current_collisioned_pair);
		}
	}

	// 1フレーム前当たっていたもの
	for (auto it = collisioned_pairs_id_.begin();it != collisioned_pairs_id_.end();)
	{
		bool now_hit = FALSE;
		// 今あたっているもの
		for (const auto& current_collisioned_pair : current_collisioned_pairs_id)
		{
			// 同じのがある場合
			if (IsSamePair(*it, current_collisioned_pair))
			{
				now_hit = TRUE;
				break;
			}
		}
		if(!now_hit)
		{
			// Exit
			auto& first_rigid_body = id_rigid_bodies_mp_[it->first];
			auto& second_rigid_body = id_rigid_bodies_mp_[it->second];
			first_rigid_body->OnCollisionExit(second_rigid_body->GetIPhysicsObject());
			second_rigid_body->OnCollisionExit(first_rigid_body->GetIPhysicsObject());
			// 要素の削除も行う
			it = collisioned_pairs_id_.erase(it);
		}
		else
		{
			++it;
		}
	}
	
	// 位置更新
	for (auto& main_id_body : id_rigid_bodies_mp_)
	{
		main_id_body.second->SetPos();
	}
}

void Physics::CheckGround()
{
	// 着地の判定
	for (auto& main_id_body : id_rigid_bodies_mp_)
	{
		auto main_body = main_id_body.second;
		bool on_ground = FALSE;
		if (!main_body->GetUseGravity()) { continue; }
		
		auto area = std::dynamic_pointer_cast<CheckMyArea>(main_body->GetIPhysicsObject());
		if (area != nullptr) { continue; }
		for (auto& target_id_body : id_rigid_bodies_mp_)
		{
			auto target_body = target_id_body.second;
			if (!target_body->GetIsActive()) { continue; }
			if (main_body == target_body) { continue; }
			if (!target_body->IsObject()) { continue; }
			auto target_area = std::dynamic_pointer_cast<CheckMyArea>(target_body->GetIPhysicsObject());
			if (target_area != nullptr) { continue;}
			Contact contact = {};
			// IPhysicsの足元当たり判定を呼びたい
			auto body = main_body->GetIPhysicsObject().get();

			// rigid_body内の足元検知用のレイと周りのオブジェクトとの当たり判定を行う
			if (CheckHitFoot(main_body, target_body,contact,kGroundProjLength))
			{
				main_body->OnGround(target_body->GetIPhysicsObject());
				on_ground = TRUE;
				break;
			}
		}

		if (!on_ground)
		{
			main_body->UnGround();
		}
	}

}

// あればTRUEを返す
bool Physics::CheckCollisionedIDPair(std::pair<int, int> id_pair)
{
	// collisioned_pairsの中に自分のpairがあるかを判断する
	
	if (collisioned_pairs_id_.size() == 0) { return FALSE; }

	// すでに衝突しているかを調べる
	for (auto& pair : collisioned_pairs_id_)
	{
		if (IsSamePair(pair, id_pair))
		{ 
			return TRUE;
		}
	}

	return FALSE;
}

bool Physics::IsSamePair(std::pair<int,int>my_pair,std::pair<int,int> target_pair)
{
	if (my_pair.first == target_pair.first && my_pair.second == target_pair.second) { return TRUE; }	// 一緒かどうか
	return FALSE;
}

bool Physics::CheckInPair(std::vector<std::pair<int, int>>pairs, std::pair<int, int> my_pair)
{
	if (pairs.size() == 0) { return FALSE; }
	for (const auto& pair : pairs)
	{
		if (IsSamePair(pair, my_pair))
		{
			return TRUE;
		}
	}

	return FALSE;
}