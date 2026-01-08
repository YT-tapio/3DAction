#pragma once
#include"DxLib.h"
#include"vector_assistant.h"
/// 押し戻しを行う
/// velocityを返す
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
		VECTOR center_to_start_pos	= VSub(start_pos, center_pos);	// 始点
		VECTOR center_to_end_pos	= VSub(end_pos, center_pos);	// 終点

		// 正射影ベクトルを取る
		VECTOR reverce_norm			= VectorAssistant::VGetReverce(norm);	// 法線を反転
		VECTOR proj_vec				= VectorAssistant::VGetProj(norm, center_to_end_pos);	

		// 終点からの押し戻し量
		VECTOR offset_pos = VSub(end_pos, proj_vec);

		// 最後に調整した座標まで伸ばす
		offset_vel = VSub(offset_pos, start_pos);

		return offset_vel;
	}

	inline VECTOR SpherePoly(const VECTOR& pos, const float& r,const VECTOR& velocity, const VECTOR& poly1, const VECTOR& poly2, const VECTOR poly3,const VECTOR& norm)
	{
		VECTOR offset_vel = VectorAssistant::VGetZero();
		// セグメントの計算をした後に法線方向に半径分押し出す
		offset_vel = SegmentPoly(pos, VAdd(pos, velocity), poly1, poly2, poly3, norm);
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


}