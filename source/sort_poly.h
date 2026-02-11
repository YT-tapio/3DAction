#pragma once
struct Contact;

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


	Contact Sort(const Contact& contact);

private:

	// •Ç‚Æ‚µ‚Ä”FŽ¯‚³‚ê‚é‚©‚Ç‚¤‚©
	const float kWallRad = 10.f;

	static const int kHitDimMax = 2048;

	SortPoly();

	bool CheckWall(const VECTOR& norm);

};