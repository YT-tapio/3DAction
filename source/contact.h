#pragma once
#include<vector>
#include"poly_contact.h"

struct Contact
{
	std::vector<PolyContact> polys;
	int hit_num = 0;
};