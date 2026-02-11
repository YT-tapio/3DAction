#include<vector>
#include"DxLib.h"
#include"sort_poly.h"
#include"contact.h"
#include"poly_contact.h"
#include"vector_assistant.h"
#include"radian_assistant.h"


Contact SortPoly::Sort(const Contact& contact)
{
	Contact all_con = {};	//‚·‚×‚Ä‚Ìƒ|ƒŠƒSƒ“‚ð“ü‚ê‚é
	Contact floor_con = {};
	int wall_num	= 0;
	int floor_num	= 0;
	for (auto& poly : contact.polys)
	{
		//•Ç‚©‚Ì”»’f‚ð‚·‚é
		if (CheckWall(poly.normal))
		{
			all_con.polys.push_back(poly);
			wall_num++;
		}
		else
		{
			floor_con.polys.push_back(poly);
			floor_num++;
		}
	}
	printfDx("wall_num : %d\n", wall_num);
	printfDx("floor_num : %d\n", floor_num);

	for (auto& poly : contact.polys)
	{
		// °‚Ìî•ñ‚ð“ü‚ê‚é
		all_con.polys.push_back(poly);
	}
	
	
	all_con.hit_num = contact.hit_num;
	return all_con;
}

SortPoly::SortPoly()
{

}

bool SortPoly::CheckWall(const VECTOR& norm)
{
	const VECTOR kVertical = VGet(0.f, 1.f, 0.f);
	const float kWallRad = RadianAssistant::kOneRad * 80.f;

	// –@ü‚ÅŒˆ‚ß‚é
	float rad = VectorAssistant::GetTwoVectorRad(kVertical, norm);
	return (rad > kWallRad);
}