#pragma once
#include"DxLib.h"
#include"vector_assistant.h"
#include"contact.h"
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

	inline VECTOR CapsuleMesh(const VECTOR& start_pos, const VECTOR& end_pos, const float& r, const VECTOR& velocity, const int& mesh,Contact& contact)
	{
		VECTOR offset_vel = velocity;
		
		// 壁からの当たり判定にする
		// 勝手にキャストしてくれる関数を作ります
		
		VECTOR old_start_pos = start_pos;
		VECTOR next_start_pos = VAdd(old_start_pos, velocity);

		for (int j = 0;j < 16;j++)
		{
			bool is_hit = FALSE;

			// この中でソートした方がいいかも
			auto hit_dim = contact.hit_dim;
			for (int i = 0; i < hit_dim.HitNum; i++)
			{
				auto poly = hit_dim.Dim[i];

				// 前のプロジェクトを参考に当たり判定をしましょう
				// 当たっているものを持ってきているからそいつとの当たり判定

				VECTOR poly_center_pos =
					VGet((poly.Position[0].x + poly.Position[1].x + poly.Position[2].x) / 3,
						(poly.Position[0].y + poly.Position[1].y + poly.Position[2].y) / 3,
						(poly.Position[0].z + poly.Position[1].z + poly.Position[2].z) / 3);

				VECTOR center_to_start = VSub(start_pos, poly_center_pos);
				VECTOR center_to_next = VSub(next_start_pos, poly_center_pos);

				VECTOR center_to_end_proj_vec = VectorAssistant::VGetZero();
				VECTOR reverce_norm = VectorAssistant::VGetReverce(poly.Normal);
				center_to_end_proj_vec = VectorAssistant::VGetProj(reverce_norm, center_to_end_proj_vec);

				VECTOR offset_pos = VSub(next_start_pos, center_to_end_proj_vec);	// 押し戻し成功
				offset_pos = VAdd(offset_pos, VScale(poly.Normal, r));						// 半径分押し戻す

				next_start_pos = offset_pos;

				// 移動した後にほかのものとぶつかっていないかを見る

				for (int k = 0; k < hit_dim.HitNum; k++)
				{
					poly = hit_dim.Dim[k];

					if (Collision::IsMoveCapsuleToMesh(old_start_pos, end_pos, offset_vel, r, mesh, contact))
					{
						// 当たっている
						is_hit = TRUE;
						break;
					}
				}

			}

			if (!is_hit)
			{
				break;
			}
		}

		

		offset_vel = VSub(next_start_pos, old_start_pos);	// 移動量分を計算する

		return offset_vel;
	}


}