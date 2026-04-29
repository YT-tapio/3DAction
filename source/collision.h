#pragma once
#include<map>
#include"DxLib.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"sphere.h"
#include"capsule.h"
#include"mesh.h"
#include"vector_assistant.h"
#include"contact.h"

//当たっているかの検地をおこないます
namespace Collision
{

	inline bool RayToTriangle(const VECTOR& ray_start_pos, const VECTOR& ray_dir, const VECTOR& tri_pos1, const VECTOR& tri_pos2, const VECTOR& tri_pos3)
	{
		const float kTolerance = 0.000001f;

		VECTOR edge1 = VSub(tri_pos2, tri_pos1);
		VECTOR edge2 = VSub(tri_pos3, tri_pos1);

		VECTOR dir_edge2_cross = VectorAssistant::VGetCross(ray_dir, edge2);

		return TRUE;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="segment_start_pos1"></param>
	/// <param name="segment_length1"></param>
	/// <param name="segment_start_pos2"></param>
	/// <param name="segment_length2"></param>
	/// <returns></returns>
	inline bool SegmentToSegment(const VECTOR& segment_start_pos1, const VECTOR& segment_length1, const VECTOR& segment_start_pos2, const VECTOR& segment_length2)
	{
		VECTOR segment_to_segment_vel = VSub(segment_start_pos2, segment_start_pos1);
		
		// 外積
		VECTOR segment_cross			= VectorAssistant::VGetCross(segment_length1,segment_length2);  //セグメントの長さ同士の
		VECTOR start_to_start_cross	= VectorAssistant::VGetCross(segment_length1, segment_length2); //セグメントとセグメントの始点から始点までのvectorの

		if (VSize(start_to_start_cross) == 0.f) { return TRUE; }
		VECTOR cross_cross = VectorAssistant::VGetCross(segment_cross, start_to_start_cross);	// 外積
		if (VSize(segment_cross) > 0 && VSize(cross_cross) == 0) { return TRUE; }

		return FALSE;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="segment_start_pos"></param>
	/// <param name="segment_length"></param>
	/// <param name="dot_pos"></param>
	/// <returns></returns>
	inline bool SegmentToPoint(const VECTOR& segment_start_pos, const VECTOR& segment_end_pos,const VECTOR& point_pos)
	{
		VECTOR start_to_dot = VSub(point_pos, segment_start_pos);
		VECTOR segment_length = VSub(segment_end_pos, segment_start_pos);
		return VectorAssistant::IsParallel(segment_length, start_to_dot);
	}

	inline bool SegmentToSphere(const VECTOR& segment_start_pos, const VECTOR& segment_end, const VECTOR& sphere_pos, const float& r)
	{
		VECTOR start_to_sphere = VSub(sphere_pos, segment_start_pos);
		VECTOR segment_length = VSub(segment_end, segment_start_pos);
		// 正射影で落とす
		VECTOR proj = VectorAssistant::VGetProj(segment_length, start_to_sphere);

		//正射影のサイズが半径サイズなら
		return VSize(proj) < r;
	}

	inline bool SegmentToCapsule(const VECTOR& segment_start_pos, const VECTOR& segment_length, const VECTOR& capsule_start_pos, const VECTOR& capsule_end_pos, const float& r)
	{


		return FALSE;
	}

	/// <summary>
	/// 球と球
	/// </summary>
	/// <param name="sphere1_pos"></param>
	/// <param name="sphere1_r"></param>
	/// <param name="sphere2_pos"></param>
	/// <param name="sphere2_r"></param>
	/// <returns></returns>
	inline bool SphereToSphere(const VECTOR& sphere1_pos,const float& sphere1_r,const  VECTOR& sphere2_pos, const float& sphere2_r)
	{
		float all_size = sphere1_r + sphere2_r;

		float dist = VectorAssistant::VGetDistSize(sphere1_pos, sphere2_pos);

		// 2つの半径を足したsizeよりも低いとき
		return (all_size > dist);
	}
	
	/// <summary>
	/// 球とカプセル
	/// </summary>
	/// <param name="sphere_pos"></param>
	/// <param name="sphere_r"></param>
	/// <param name="capsule_start_pos"></param>
	/// <param name="capsule_end_pos"></param>
	/// <param name="capsule_r"></param>
	/// <returns></returns>
	inline bool SphereToCapsule(const VECTOR& sphere_pos,const float& sphere_r, const VECTOR& capsule_start_pos, const VECTOR& capsule_end_pos, const float& capsule_r)
	{
		float all_size = sphere_r + capsule_r;

		// 最初に球と球の当たり判定を行う
		if (SphereToSphere(sphere_pos, sphere_r, capsule_start_pos, capsule_r)) { return TRUE; }
		if (SphereToSphere(sphere_pos, sphere_r, capsule_end_pos, capsule_r)) { return TRUE; }

		VECTOR start_to_dist = VSub(sphere_pos,capsule_start_pos);
		VECTOR start_to_end_dist = VSub(capsule_end_pos, capsule_start_pos);
		VECTOR proj_vel = VectorAssistant::VGetProj(start_to_end_dist, start_to_dist);

		//startのposからproj_velを足した場所の距離を見る
		// 一番近い場所までの距離
		float near_dist = VectorAssistant::VGetDistSize(sphere_pos, VAdd(capsule_start_pos, proj_vel));

		return (all_size > near_dist);
	}

	/// <summary>
	/// カプセルとカプセル
	/// </summary>
	/// <param name="capsule1_start_pos"></param>
	/// <param name="capsule1_end_pos"></param>
	/// <param name="capsule1_r"></param>
	/// <param name="capsule2_start_pos"></param>
	/// <param name="capsule2_end_pos"></param>
	/// <param name="capsule2_r"></param>
	/// <returns></returns>
	inline bool CapsuleToCapsule(const VECTOR& capsule1_start_pos, const VECTOR &capsule1_end_pos,const float& capsule1_r, 
		const VECTOR& capsule2_start_pos, const VECTOR& capsule2_end_pos, const float& capsule2_r)
	{
		float all_size = capsule1_r + capsule2_r;


		float dist_size = 0.f;
		VECTOR capsule1_segment = VSub(capsule1_end_pos,capsule1_start_pos);
		VECTOR capsule2_segment = VSub(capsule2_end_pos, capsule2_start_pos);

		// 垂直の例外処理
		if (VectorAssistant::IsParallel(capsule1_segment, capsule2_segment))
		{
			// 始点からの距離を見て判別
			float dist = VSize(VSub(capsule1_start_pos, capsule2_start_pos));
			return (dist < all_size);
		}

		dist_size = VectorAssistant::VGetSegmentDistSize(capsule1_start_pos, capsule1_end_pos, capsule2_start_pos, capsule2_end_pos);

		return (all_size > dist_size);
	}

	inline bool IsMoveSphereToSphere(const VECTOR& sphere1_pos, const float& sphere1_r, const VECTOR& sphere1_velocity,
		const VECTOR& sphere2_pos, const float& sphere2_r, const VECTOR& sphere2_velocity)
	{

		VECTOR sphere1_future_pos = VAdd(sphere1_pos, sphere1_velocity);
		VECTOR sphere2_future_pos = VAdd(sphere2_pos, sphere2_velocity);

		return CapsuleToCapsule(sphere1_pos, sphere1_future_pos, sphere1_r, sphere2_pos, sphere2_future_pos, sphere2_r);
	}

	inline bool IsMoveSphereToCapsule(const VECTOR& sphere_pos, const float& sphere_r, const VECTOR& sphere_velocity,
		const VECTOR& capsule_start_pos, const VECTOR& capsule_end_pos, const float& capsule_r, const VECTOR& capsule_velocity)
	{
		
		VECTOR sphere_future_pos = VAdd(sphere_pos, sphere_velocity);

		// 移動のカプセルを作る
		float capsule_vel_size = VSize(capsule_velocity);
		float capsule_diameter = capsule_r * 2.f;	// まずは直径を出す
		
		int capsule_add_num = 0;

		if (capsule_vel_size > capsule_diameter)
		{
			capsule_add_num = ((capsule_vel_size - capsule_diameter) / capsule_diameter) + 1.f;
		}

		int capsule_max = capsule_add_num + 2;

		for (int i = 0; i < capsule_max; i++)
		{
			VECTOR capsule_offset_vel = VectorAssistant::VGetZero();	//どのくらい離れているか
			if (i != 0) { capsule_offset_vel = VScale(capsule_velocity, i / (capsule_max - 1)); }
			VECTOR offset_capsule_start_pos = VAdd(capsule_start_pos, capsule_offset_vel);		// 調整した始点
			VECTOR offset_capsule_end_pos = VAdd(capsule_end_pos, capsule_offset_vel);		// 調整した終点

			if (CapsuleToCapsule(sphere_pos, sphere_future_pos, sphere_r, offset_capsule_start_pos, offset_capsule_end_pos, capsule_r))
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	inline bool IsMoveCapsuleToCapsule(const VECTOR& capsule1_start_pos, const VECTOR& capsule1_end_pos, const float& capsule1_r, const VECTOR& capsule1_velocity,
		const VECTOR& capsule2_start_pos, const VECTOR& capsule2_end_pos, const float& capsule2_r, const VECTOR& capsule2_velocity)
	{
		// 移動量
		float capsule1_vel_size = VSize(capsule1_velocity);
		float capsule2_vel_size = VSize(capsule2_velocity);
		// 直径
		float capsule1_diameter = capsule1_r * 2.f;
		float capsule2_diameter = capsule2_r * 2.f;
		// 追加する数
		int capsule1_add_num = 0;
		int capsule2_add_num = 0;
		// 移動量のサイズが直径を超えているとき新たにカプセルを追加する
		if (capsule1_vel_size > capsule1_diameter)
		{
			// 最低でも一つ
			capsule1_add_num = ((capsule1_vel_size - capsule1_diameter) / capsule1_diameter) + 1.f;
		}

		if (capsule2_vel_size > capsule2_diameter)
		{
			capsule2_add_num = ((capsule2_vel_size - capsule2_diameter) / capsule2_diameter) + 1.f;
		}
		
		int capsule1_max = capsule1_add_num + 2;
		int capsule2_max = capsule2_add_num + 2;
		for (int j = 0;j < capsule1_max;j++)
		{
			VECTOR capsule1_offset_vel			= VectorAssistant::VGetZero();	//どのくらい離れているか
			if (j != 0) { capsule1_offset_vel		= VScale(capsule1_velocity, j / (capsule1_max - 1)); }
			VECTOR offset_capsule1_start_pos	= VAdd(capsule1_start_pos, capsule1_offset_vel);	// 調整した始点
			VECTOR offset_capsule1_end_pos	= VAdd(capsule1_end_pos, capsule1_offset_vel);		// 調整した終点
			for (int i = 0; i < capsule2_max; i++)
			{
				VECTOR capsule2_offset_vel = VectorAssistant::VGetZero();	// どのくらい離れているか
				if (i != 0) { capsule2_offset_vel = VScale(capsule2_velocity, i / (capsule2_max - 1)); }
				VECTOR offset_capsule2_start_pos = VAdd(capsule2_start_pos, capsule2_offset_vel);	// 調整した始点
				VECTOR offset_capsule2_end_pos = VAdd(capsule2_end_pos, capsule2_offset_vel);		// 調整した終点
				if (CapsuleToCapsule(offset_capsule1_start_pos, offset_capsule1_end_pos, capsule1_r, offset_capsule2_start_pos, offset_capsule2_end_pos, capsule2_r)) 
				{ 
					return TRUE;
				}
			}
		}

		return FALSE;
	}



	inline bool SegmentToMesh(const VECTOR& start_pos, const VECTOR& end_pos, const int& mesh,Contact& contact)
	{
		auto hit_dim	= MV1CollCheck_LineDim(mesh, -1, start_pos, end_pos);
		bool is_hit = (hit_dim.HitNum > 0);
		if (is_hit)
		{
			contact.hit_num = hit_dim.HitNum;
			for (int i = 0; i < contact.hit_num; i++)
			{
				auto poly = hit_dim.Dim[i];
				PolyContact poly_con;

				poly_con.position[0]	= poly.Position[0];
				poly_con.position[1]	= poly.Position[1];
				poly_con.position[2]	= poly.Position[2];
				poly_con.normal			= poly.Normal;

				contact.polys.push_back(poly_con);
			}
		}
		MV1CollResultPolyDimTerminate(hit_dim);
		return is_hit;
	}

	// 移動を考慮しない
	inline bool SphereToMesh(const VECTOR& pos,const float& r,const int& mesh,Contact& contact)
	{
		auto hit_dim = MV1CollCheck_Sphere(mesh, -1, pos, r);
		bool is_hit = (hit_dim.HitNum > 0);

		if (is_hit)
		{
			contact.hit_num = hit_dim.HitNum;
			for (int i = 0; i < hit_dim.HitNum; i++)
			{
				auto poly = hit_dim.Dim[i];
				PolyContact poly_con;

				poly_con.position[0] = poly.Position[0];
				poly_con.position[1] = poly.Position[1];
				poly_con.position[2] = poly.Position[2];

				poly_con.normal = poly.Normal;

				// 追加
				contact.polys.push_back(poly_con);
			}
		}
		MV1CollResultPolyDimTerminate(hit_dim);
		return is_hit;
	}

	// 移動を考慮しない
	inline bool CapsuleToMesh(const VECTOR& start_pos, const VECTOR& end_pos,const float& r,const int& mesh,Contact& contact)
	{
		auto hit_dim = MV1CollCheck_Capsule(mesh, -1, start_pos, end_pos, r);
		bool is_hit = (hit_dim.HitNum > 0);
		if (is_hit)
		{
			contact.hit_num = hit_dim.HitNum;
			for (int i = 0; i < hit_dim.HitNum; i++)
			{
				auto poly = hit_dim.Dim[i];
				PolyContact poly_con;

				poly_con.position[0] = poly.Position[0];
				poly_con.position[1] = poly.Position[1];
				poly_con.position[2] = poly.Position[2];

				poly_con.normal = poly.Normal;

				// 追加
				contact.polys.push_back(poly_con);
			}
		}
		MV1CollResultPolyDimTerminate(hit_dim);
		return is_hit;
	}

	// 移動を考慮した関数
	inline bool IsMoveSphereToMesh(const VECTOR& center_pos, const VECTOR& velocity,const float& r, const int& mesh, Contact& contact)
	{
		// 球の移動はカプセルになる
		bool is_hit = CapsuleToMesh(center_pos, VAdd(center_pos, velocity), r, mesh,contact);
		return is_hit;
	}

	// 移動を加味した関数(start_pos : カプセルの始点,end_pos : カプセルの終点)
	inline bool IsMoveCapsuleToMesh(const VECTOR& start_pos, const VECTOR& end_pos, const VECTOR& velocity,const float& r, const int& mesh,Contact& contact)
	{
		VECTOR capsule_segment	= VSub(end_pos, start_pos);
		VECTOR future_start_pos = VAdd(start_pos, velocity);

		bool is_hit = FALSE;
		float offset_r = r - 0.1f;
		// 移動前後のカプセルが当たっているかを判定
		if (CapsuleToMesh(start_pos, end_pos, offset_r, mesh,contact))										{ is_hit = TRUE; }
		if (CapsuleToMesh(future_start_pos, VAdd(future_start_pos, capsule_segment), r, mesh, contact))		{ is_hit = TRUE; }

		// どちらも当たらないなら
		const int kDefaultCapsuleNum	= 2;
		const int kDiameter				= r * 2;			// 直径
		const int kDetectionCapsuleMax	= 100;	// カプセルの量に最大値を設ける
		
		if (TRUE)
		{
			VECTOR capsule_old_start_pos	= start_pos;
			VECTOR capsule_old_end_pos		= end_pos;
			VECTOR capsule_next_start_pos	= VAdd(capsule_old_start_pos, velocity);
			VECTOR capsule_next_end_pos		= VAdd(capsule_old_end_pos, velocity);
			
			if (CapsuleToMesh(capsule_old_start_pos, capsule_next_start_pos, offset_r,mesh, contact))	{ is_hit = TRUE; }
			if (CapsuleToMesh(capsule_old_end_pos, capsule_next_end_pos, offset_r,mesh, contact))		{ is_hit = TRUE; }

			return is_hit;

		}
		else
		{
			// 移動量を直径分引いておく
			float dist = VSize(velocity) - kDiameter;
			int capsule_num = dist / kDiameter + 1;	//最低1個はある

			// セグメントの当たり判定する
			bool is_hit = FALSE;
			is_hit = SegmentToMesh(start_pos, VAdd(start_pos, velocity), mesh, contact);
			if (is_hit) { return TRUE; }
			is_hit = SegmentToMesh(end_pos, VAdd(end_pos, velocity), mesh, contact);
			if (is_hit) { return TRUE; }

			if (capsule_num < kDetectionCapsuleMax)
			{
				for (int i = 0; i < capsule_num; i++)
				{
					int num = i + 1;					// 例 : ●〇〇〇● (〇)以外は検出済みなのでその分プラス
					float ratio = num / (capsule_num + 1);	// 比を作る

					VECTOR offset_capsule_start_pos = VAdd(start_pos, VScale(velocity, ratio));
					if (CapsuleToMesh(offset_capsule_start_pos, VAdd(offset_capsule_start_pos, capsule_segment), r, mesh, contact)) { return TRUE; }
				}
			}
			else
			{
				// セグメントの当たり判定する
				bool is_hit = FALSE;
				is_hit = SegmentToMesh(start_pos, VAdd(start_pos, velocity), mesh, contact);
				if (is_hit) { return TRUE; }
				is_hit = SegmentToMesh(end_pos, VAdd(end_pos, velocity), mesh, contact);
				return is_hit;
			}
		}
		
		return FALSE;
	}

	inline bool HitCheckSphereTriangle(const VECTOR& old_center_pos, const float& r, const VECTOR& velocity, const VECTOR& tri_pos1, const VECTOR& tri_pos2, const VECTOR& tri_pos3)
	{
		VECTOR next_center_pos = VAdd(old_center_pos, velocity);
		float check_hit_radius = r - (r * 0.1f);

		if (HitCheck_Sphere_Triangle(next_center_pos, r, tri_pos1, tri_pos2, tri_pos3)) { return TRUE; }// 未来のsphereの当たり判定
		if (HitCheck_Capsule_Triangle(old_center_pos, next_center_pos, check_hit_radius, tri_pos1, tri_pos2, tri_pos3)) { return TRUE; }	// 移動量の当たり判定
		
		return FALSE;
	}

	inline bool HitCheckCapsuleTriangle(const VECTOR& old_start_pos, const VECTOR& old_end_pos, const float& r, const VECTOR& velocity, const VECTOR& tri_pos1, const VECTOR& tri_pos2, const VECTOR& tri_pos3)
	{
		VECTOR next_start_pos	= VAdd(old_start_pos, velocity);
		VECTOR next_end_pos		= VAdd(old_end_pos, velocity);
		VECTOR capsule_segment	= VSub(old_end_pos, old_start_pos);
	
		float check_hit_radius = r - (r * 0.1f);

		// 未来のカプセルの当たり判定
		if (HitCheck_Capsule_Triangle(next_start_pos, next_end_pos	, r, tri_pos1, tri_pos2, tri_pos3))		{ return TRUE; }
		if (HitCheck_Capsule_Triangle(old_start_pos, next_start_pos, check_hit_radius, tri_pos1, tri_pos2, tri_pos3)) { return TRUE; }
		if (HitCheck_Capsule_Triangle(old_end_pos, next_end_pos, check_hit_radius, tri_pos1, tri_pos2, tri_pos3)) { return TRUE; }
		
		float diameter				= (r * 2);	//直径
		VECTOR velocity_center_pos	= VAdd(old_start_pos, VScale(velocity, 0.5f));//さきにvelocityの間のpos

		float space_size			= VSize(velocity) - diameter;	// カプセルの間のサイズ
		//スペースが直径よりも小さい場合 : 強制的に直径の大きさにする
		if (space_size < diameter){ space_size = diameter; }

		float space_r = space_size * 0.5f;
		return HitCheck_Capsule_Triangle(velocity_center_pos, capsule_segment, space_r, tri_pos1, tri_pos2, tri_pos3);
	}

}
