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

	//coll_pos(capsule‚ÌˆÚ“®‘O)
	Contact Sort(const Contact& contact, const VECTOR& pos);

private:

	// •Ç‚Æ‚µ‚Ä”F¯‚³‚ê‚é‚©‚Ç‚¤‚©
	const float kWallRad = 10.f;

	static const int kHitDimMax = 2048;

	SortPoly();

	bool CheckWall(const VECTOR& norm);

	//‹ß‚¢‡‚É•À‚×‚é
	std::vector<PolyContact> ClosestOrder(std::vector<PolyContact> polys,const VECTOR& pos);

};