#pragma once
#include<iostream>
#include"DxLib.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"sphere.h"
#include"capsule.h"
//#include"AABB.h"
//#include"OBB.h"
#include"mesh.h"

#include"vector_assistant.h"


//当たっているかの検地をおこないます
namespace Collision
{

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

	inline bool SphereToMesh(const VECTOR& pos,const float& r,const int& mesh)
	{
		auto poly = MV1CollCheck_Sphere(mesh, -1, pos, r);
		bool is_hit = (poly.HitNum != 0);

		return is_hit;
	}

	inline bool CapsuleToMesh(const VECTOR& start_pos, const VECTOR& end_pos,const float& r,const int& mesh)
	{
		auto poly = MV1CollCheck_Capsule(mesh, -1, start_pos, end_pos, r);
		bool is_hit = (poly.HitNum != 0);

		return is_hit;
	}
}
