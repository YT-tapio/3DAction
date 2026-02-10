#pragma once


class SortPoly
{
public:

	SortPoly();

	~SortPoly();

	MV1_COLL_RESULT_POLY_DIM* Sort(MV1_COLL_RESULT_POLY_DIM* hit_dim);

private:
	
	// •Ç‚Æ‚µ‚Ä”FŽ¯‚³‚ê‚é‚©‚Ç‚¤‚©
	const float kWallRad = 10.f;

	static const int kHitDimMax = 2048;


};