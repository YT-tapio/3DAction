#pragma once
#include<vector>
#include<unordered_map>
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

	//同じ情報を消去する
	std::unordered_map<int, PolyContact> poly_mp;

	int i = 0;
	for (auto poly : contact.polys)
	{
		if (i == 0)
		{
			poly_mp[i] = poly;
		}

		//今までのpolyと一緒だとmapに入れない
		for (auto map_poly = poly_mp.begin(); map_poly != poly_mp.end(); map_poly++)
		{
			
		}


		i++;
	}


}