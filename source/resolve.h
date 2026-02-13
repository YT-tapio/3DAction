#pragma once
#include"DxLib.h"
#include"vector_assistant.h"
#include"contact.h"
#include"sort_poly.h"

/// 押し戻しを行う(velocityを返す)
namespace Resolve
{

	inline VECTOR CapsuleCapsule()
	{

	}

	//セグメントとポリゴンの押し戻し(壁ずり)
	inline VECTOR SegmentPoly(const VECTOR& start_pos,const VECTOR& end_pos,const VECTOR& poly1,const VECTOR& poly2, const VECTOR poly3, const VECTOR& norm)
	{
		VECTOR offset_vel = VectorAssistant::VGetZero();

		// ポリゴンのセンターを取る
		VECTOR	center_pos = VAdd(VAdd(poly1, poly2), poly3);			// 初期化
				center_pos = VectorAssistant::VDevide(center_pos, 3);	// 重点を出す

		// センターからの距離を取る
		VECTOR center_to_end	= VSub(end_pos, center_pos);	// 終点

		// 正射影ベクトルを取る
		VECTOR reverce_norm			= VectorAssistant::VGetReverce(norm);	// 法線を反転
		VECTOR proj_vec				= VectorAssistant::VGetProj(reverce_norm, center_to_end);

		// 終点からの押し戻し量
		VECTOR offset_pos = VSub(end_pos, proj_vec);

		// 最後に調整した座標まで伸ばす
		offset_vel = VSub(offset_pos, start_pos);

		return offset_vel;
	}

	inline VECTOR SpherePoly(const VECTOR& center_pos, const float& r,const VECTOR& velocity, const VECTOR& poly1, const VECTOR& poly2, const VECTOR poly3,const VECTOR& norm)
	{
		VECTOR offset_vel = VectorAssistant::VGetZero();
		// セグメントの計算をした後に法線方向に半径分押し出す
		offset_vel = SegmentPoly(center_pos, VAdd(center_pos, velocity), poly1, poly2, poly3, norm);
		offset_vel = VAdd(offset_vel, VScale(norm, r));
		
		return offset_vel;
	}

	inline VECTOR CapsulePoly(const VECTOR& start_pos, const VECTOR& end_pos,const float& r,const VECTOR& velocity, const VECTOR& poly1, const VECTOR& poly2, const VECTOR poly3, const VECTOR& norm)
	{
		VECTOR offset_vel = VectorAssistant::VGetZero();
		// セグメントの計算をした後に法線方向に半径分押し出す
		offset_vel = SegmentPoly(start_pos, VAdd(start_pos, velocity), poly1, poly2, poly3, norm);
		offset_vel = VAdd(offset_vel, VScale(norm, r));

		return offset_vel;
	}

	inline VECTOR SegmentMesh(const VECTOR& start_pos, const VECTOR& end_pos, const int& mesh, Contact& contact)
	{
		VECTOR offset_vel = VSub(start_pos, end_pos);	// セグメントの長さを取る
		VECTOR segment_end_pos = end_pos;

		CheckSamePoly(contact);		//contactの中に同じポリゴンの情報があれば除外する。
		contact = SortPoly::GetInstance().Sort(contact, start_pos);	// ソート

		for (auto& poly : contact.polys)
		{
			offset_vel = SegmentPoly(start_pos, end_pos, poly.position[0], poly.position[1], poly.position[2], poly.normal);
			segment_end_pos = VAdd(start_pos, offset_vel);
		}
		return offset_vel;
	}

	inline VECTOR SphereMesh(const VECTOR& center_pos, const float& r, const VECTOR& velocity, const int& mesh, Contact& contact)
	{
		VECTOR offset_vel = velocity;

		// 壁からの当たり判定にする
		// 勝手にキャストしてくれる関数を作ります
		VECTOR old_center_pos = center_pos;
		VECTOR next_center_pos = VAdd(old_center_pos, velocity);
		VECTOR original_old_pos = VAdd(old_center_pos, VGet(0.f, -r, 0.f));

		for (int j = 0; j < 16; j++)
		{
			bool is_hit = FALSE;
			// この中でソートした方がいいかも
			CheckSamePoly(contact);		//contactの中に同じポリゴンの情報があれば除外する。
			contact = SortPoly::GetInstance().Sort(contact, original_old_pos);	// ソート
			for (auto& poly : contact.polys)
			{
				// 当たっているものを持ってきているからそいつとの当たり判定
				// すでに押し戻されている可能性もあるため再度当たっているかの確認を行う
				// segmentとの当たり判定 || 未来のcolliderの当たり判定
				bool is_hit_triangle = Collision::HitCheckSphereTriangle(old_center_pos, r, offset_vel, poly.position[0], poly.position[1], poly.position[2]);

				if (is_hit_triangle)
				{
					offset_vel = SpherePoly(old_center_pos, r, offset_vel, poly.position[0], poly.position[1], poly.position[2], poly.normal);
					next_center_pos = VAdd(old_center_pos, offset_vel);
				}
			}

		}

		return offset_vel;
	}

	inline VECTOR CapsuleMesh(const VECTOR& start_pos, const VECTOR& end_pos, const float& r, const VECTOR& velocity, const int& mesh,Contact& contact)
	{
		VECTOR offset_vel = velocity;
		
		// 壁からの当たり判定にする
		// 勝手にキャストしてくれる関数を作ります
		VECTOR original_old_pos = VAdd(start_pos, VGet(0.f, -r, 0.f));
		VECTOR old_start_pos	= start_pos;
		VECTOR old_end_pos		= end_pos;
		VECTOR next_start_pos	= VAdd(old_start_pos, offset_vel);
		VECTOR next_end_pos		= VAdd(old_end_pos, offset_vel);

		for (int j = 0;j < 16;j++)
		{
			bool is_hit = FALSE;
			// この中でソートした方がいいかも
			CheckSamePoly(contact);		//contactの中に同じポリゴンの情報があれば除外する。
			contact = SortPoly::GetInstance().Sort(contact,original_old_pos);	// ソート
			for (auto& poly : contact.polys)
			{
				// 当たっているものを持ってきているからそいつとの当たり判定
				// すでに押し戻されている可能性もあるため再度当たっているかの確認を行う
				// segmentとの当たり判定 || 未来のcolliderの当たり判定
				bool is_hit_triangle = Collision::HitCheckCapsuleTriangle(old_start_pos, old_end_pos, r, offset_vel, poly.position[0], poly.position[1], poly.position[2]);

				if (is_hit_triangle)
				{
					offset_vel		= CapsulePoly(old_start_pos, old_end_pos, r, offset_vel, poly.position[0], poly.position[1], poly.position[2], poly.normal);
					next_start_pos	= VAdd(old_start_pos, offset_vel);
					next_end_pos	= VAdd(old_end_pos, offset_vel);
				}

			}
		}

		return offset_vel;
	}


}