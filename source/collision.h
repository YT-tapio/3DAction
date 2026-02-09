#pragma once
#include<map>
#include"DxLib.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"sphere.h"
#include"capsule.h"
#include"mesh.h"
#include"vector_assistant.h"


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


		return TRUE;
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

		dist_size = VectorAssistant::VGetSegmentDist(capsule1_start_pos, capsule1_end_pos, capsule2_start_pos, capsule2_end_pos);

		return (all_size > dist_size);
	}

	inline bool SegmentToMesh(const VECTOR& start_pos, const VECTOR& end_pos, const int& mesh)
	{
		auto poly = MV1CollCheck_Line(mesh, -1, start_pos, end_pos);
		return poly.HitFlag;
	}

	// 移動を考慮しない
	inline bool SphereToMesh(const VECTOR& pos,const float& r,const int& mesh)
	{
		auto poly = MV1CollCheck_Sphere(mesh, -1, pos, r);
		bool is_hit = (poly.HitNum != 0);
		return is_hit;
	}

	// 移動を考慮しない
	inline bool CapsuleToMesh(const VECTOR& start_pos, const VECTOR& end_pos,const float& r,const int& mesh)
	{
		auto poly = MV1CollCheck_Capsule(mesh, -1, start_pos, end_pos, r);
		bool is_hit = (poly.HitNum != 0);
		return is_hit;
	}

	// 移動を考慮した関数
	inline bool IsMoveSphereToMesh(const VECTOR& pos, const VECTOR& velocity,const float& r, const int& mesh)
	{
		// 球の移動はカプセルになる
		bool is_hit = CapsuleToMesh(pos, VAdd(pos, velocity), r, mesh);
		return is_hit;
	}

	// 移動を加味した関数
	inline bool IsMoveCapsuleToMesh(const VECTOR& start_pos, const VECTOR& end_pos, const VECTOR& velocity,const float& r, const int& mesh)
	{
		VECTOR capsule_segment	= VSub(end_pos, start_pos);
		VECTOR future_start_pos = VAdd(start_pos, velocity);

		// 移動前後のカプセルが当たっているかを判定
		
		if (CapsuleToMesh(start_pos, end_pos, r, mesh)) { return TRUE; }
		if (CapsuleToMesh(future_start_pos, VAdd(future_start_pos, capsule_segment), r, mesh)) { return TRUE; }

		// どちらも当たらないなら
		const int kDefaultCapsuleNum = 2;
		const int kDiameter = r * 2;			// 直径
		const int kDetectionCapsuleMax = 100;	// カプセルの量に最大値を設ける
		// 移動量を直径分引いておく
		float dist = VSize(velocity) - kDiameter;

		int capsule_num = dist / kDiameter + 1;	//最低1個はある
		
		if (capsule_num < kDetectionCapsuleMax)
		{
			for (int i = 0; i < capsule_num; i++)
			{
				int num = i + 1;					// 例 : ●〇〇〇● (〇)以外は検出済みなのでその分プラス
				float ratio = num / (capsule_num + 1);	// 比を作る

				VECTOR offset_capsule_start_pos = VAdd(start_pos, VScale(velocity, ratio));
				if (CapsuleToMesh(offset_capsule_start_pos, VAdd(offset_capsule_start_pos, capsule_segment), r, mesh)) { return TRUE; }
			}
		}
		else
		{
			// セグメントの当たり判定する
			bool is_hit = FALSE;
			is_hit = SegmentToMesh(start_pos, VAdd(start_pos, velocity), mesh);
			if (is_hit) { return TRUE; }
			is_hit = SegmentToMesh(end_pos, VAdd(end_pos, velocity), mesh);
			return is_hit;
		}
		return FALSE;
	}

}
