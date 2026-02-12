#pragma once
#include<vector>
#include<unordered_map>
#include"vector_assistant.h"
#include"poly_contact.h"

struct Contact
{
	std::vector<PolyContact> polys;
	int hit_num = 0;
};

inline void CheckSamePoly(Contact& contact)
{
	Contact con = contact;		// contactの情報をコピー
	con.polys.clear();			// conの要素を消去

	//同じ情報をいれないもの
	std::vector<PolyContact> not_same_polys;

	for (auto& target_poly : contact.polys)
	{
		//要素がからの場合は最初に代入しておく
		if (not_same_polys.empty()) { not_same_polys.push_back(target_poly); continue; }
		//今までのpolyと一緒だとmapに入れない
		bool is_same = FALSE;
		for (auto& offset_poly : not_same_polys)
		{
			// 各頂点、法線がすべて同じなら
			if (VectorAssistant::IsSamePos(offset_poly.position[0]	, target_poly.position[0]) && 
				VectorAssistant::IsSamePos(offset_poly.position[1]	, target_poly.position[1]) &&
				VectorAssistant::IsSamePos(offset_poly.position[2]	, target_poly.position[2]) &&
				VectorAssistant::IsSamePos(offset_poly.normal		, target_poly.normal))
			{
				is_same = TRUE;
				break;
			}
		}
		// 同じじゃない
		if(!is_same) { not_same_polys.push_back(target_poly); }
	}
	con.polys = not_same_polys;
	contact = con;

}