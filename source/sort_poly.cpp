#include<vector>
#include<map>
#include<algorithm>
#include<iterator>
#include"DxLib.h"
#include"sort_poly.h"
#include"contact.h"
#include"poly_contact.h"
#include"vector_assistant.h"
#include"radian_assistant.h"


Contact SortPoly::Sort(const Contact& contact,const VECTOR& pos)
{
	const float kInSide = RadianAssistant::kOneRad * 90.f;

	Contact all_con = contact;	//すべてのポリゴンを入れる
	all_con.polys.clear();
	std::vector<PolyContact> wall_polys;
	std::vector<PolyContact> floor_polys;
	for (auto& poly : contact.polys)
	{
		VECTOR center_pos			= VectorAssistant::VDevide(VAdd(VAdd(poly.position[0], poly.position[1]), poly.position[2]), 3);
		VECTOR center_to_coll_dist	= VSub(pos, center_pos);		//中心点から移動前のcollの始点までのやつ
		
		float rad = VectorAssistant::GetTwoVectorRad(poly.normal, center_to_coll_dist);

		// 90度よりも高いなら
		if (rad > kInSide) { continue; }

		//壁かの判断をする
		if (CheckWall(poly.normal))
		{
			wall_polys.push_back(poly);
		}
		else
		{
			floor_polys.push_back(poly);
		}
	}
	
	wall_polys		= ClosestOrder(wall_polys, pos);	// 壁の中でも近いものをソートする
	floor_polys		= ClosestOrder(floor_polys, pos);	// 床の中でも近いものをソートする

	all_con.polys.insert(all_con.polys.end(), wall_polys.begin(), wall_polys.end());
	all_con.polys.insert(all_con.polys.end(), floor_polys.begin(), floor_polys.end());
	
	return all_con;
}

SortPoly::SortPoly()
{

}

bool SortPoly::CheckWall(const VECTOR& norm)
{
	const VECTOR kVertical	= VGet(0.f, 1.f, 0.f);
	const float kWallRad	= RadianAssistant::kOneRad * 80.f;

	// 法線で決める
	float rad = VectorAssistant::GetTwoVectorRad(kVertical, norm);
	return (rad > kWallRad);
}

std::vector<PolyContact> SortPoly::ClosestOrder(std::vector<PolyContact> polys,const VECTOR& pos)
{
	std::vector<PolyContact> return_polys;
	// 最初に距離をとる
	std::map<float, PolyContact> sort_polys_mp;	//マップにいれる、勝手にソートしてくれる
	for (auto& poly : polys)
	{
		VECTOR poly_center_pos = VectorAssistant::VDevide(VAdd(VAdd(poly.position[0], poly.position[1]), poly.position[2]), 3);

		// polyの頂点たちを見てその中でも一番距離が近いものを入れる
		float vertex1_dist_size = VectorAssistant::VGetDistSize(pos, poly.position[0]);
		float vertex2_dist_size = VectorAssistant::VGetDistSize(pos, poly.position[1]);
		float vertex3_dist_size = VectorAssistant::VGetDistSize(pos, poly.position[2]);
		float center_dist_size	= VectorAssistant::VGetDistSize(pos, poly_center_pos);
		// いちばんちいさいものにする
		float	near_dist_size	= (vertex1_dist_size > vertex2_dist_size) ? vertex2_dist_size : vertex1_dist_size;
				near_dist_size	= (near_dist_size	 > vertex3_dist_size) ? vertex3_dist_size : near_dist_size;
				near_dist_size	= (near_dist_size	> center_dist_size)	  ? center_dist_size  : near_dist_size;
		//printfDx("%d個目 : %.2f\n", i, near_dist_size);
		sort_polys_mp[near_dist_size] = poly;
		
	}

	// mapのサイズを先に確保
	return_polys.reserve(sort_polys_mp.size());
	std::transform(sort_polys_mp.begin(), sort_polys_mp.end(), std::back_inserter(return_polys),
		[](const auto& poly) {return poly.second; });		// mapの中身を繰り返す。secondでvalue(PolyContact)を取り出す

	return return_polys;
}