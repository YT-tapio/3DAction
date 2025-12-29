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
		float all_size = capsule1_r * capsule2_r;
		
		if (FALSE)
		{
			
			// 近いとことの距離 : 最初は絶対当たらないように
			VECTOR near_vel = VectorAssistant::VGetSame(all_size);
			// カプセル1のレイ(線分)を取る
			VECTOR capsule1_start_to_dist = VSub(capsule1_end_pos, capsule1_start_pos);

			// カプセル1のstart_posからカプセル2のstart_posとの距離を取る
			VECTOR capsule1_start_to_capsule2_start = VSub(capsule2_start_pos, capsule1_start_pos);
			VECTOR capsule1_start_to_capsule2_end = VSub(capsule2_end_pos, capsule1_start_pos);

			//VECTOR
		}
		float dist_size = 0.f;
		VECTOR capsule1_segment = VSub(capsule1_end_pos,capsule1_start_pos);
		VECTOR capsule2_segment = VSub(capsule2_end_pos, capsule2_start_pos);
		VECTOR capsule1_start_to_capsule2_start_dist = VSub(capsule2_start_pos, capsule1_start_pos);

		dist_size = VectorAssistant::VGetLineNearDist(capsule1_segment, capsule2_segment, capsule1_start_to_capsule2_start_dist);

		return (all_size > dist_size);
	}

	inline bool SphereToMesh()
	{



		
		return TRUE;
	}

	inline bool CapsuleToMesh()
	{


		return FALSE;
	}
}
