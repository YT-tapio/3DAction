#include"DxLib.h"
#include"sort_poly.h"

SortPoly::SortPoly()
{

}

SortPoly::~SortPoly()
{

}

MV1_COLL_RESULT_POLY_DIM* SortPoly::Sort(MV1_COLL_RESULT_POLY_DIM* hit_dim)
{
	
	MV1_COLL_RESULT_POLY_DIM* all_dim;

	int wall_num	= 0;
	int floor_num	= 0;

	MV1_COLL_RESULT_POLY_DIM* wall_dim[kHitDimMax];
	MV1_COLL_RESULT_POLY_DIM* floor_dim[kHitDimMax];


	for (int i = 0; i < hit_dim->HitNum; i++)
	{
		auto poly = hit_dim->Dim[i];
		poly.Normal;


	}


	return hit_dim;
}