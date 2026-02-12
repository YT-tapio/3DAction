#pragma once

struct Contact;
struct PolyContact;

class SortPoly
{
public:

	static SortPoly& GetInstance()
	{
		static SortPoly instance;
		return instance;
	}

	SortPoly(const SortPoly&) = delete;
	SortPoly& operator = (const SortPoly&) = delete;


	Contact Sort(const Contact& contact, const VECTOR& pos);

private:

	// ï«Ç∆ÇµÇƒîFéØÇ≥ÇÍÇÈÇ©Ç«Ç§Ç©
	const float kWallRad = 10.f;

	static const int kHitDimMax = 2048;

	SortPoly();

	bool CheckWall(const VECTOR& norm);

	//ãﬂÇ¢èáÇ…ï¿Ç◊ÇÈ
	std::vector<PolyContact> ClosestOrder(std::vector<PolyContact> polys,const VECTOR& pos);

};