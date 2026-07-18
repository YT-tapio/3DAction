#pragma once
#include<functional>

struct ActiveStatModifireUI
{
	std::function<bool()> end_condition = nullptr;	// I—¹ğŒ
	int handle = -1;
};