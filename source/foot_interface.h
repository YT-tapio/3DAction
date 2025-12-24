#pragma once
#include<iostream>

class IGround : public std::enable_shared_from_this<IGround>
{
public:
	virtual ~IGround() = default;

	/// <summary>
	/// “–‚½‚Á‚Ä‚¢‚é
	/// </summary>
	virtual void OnGrounded() = 0;

	/// <summary>
	/// “–‚½‚Á‚Ä‚¢‚È‚¢
	/// </summary>
	virtual void OnUnGrounded() = 0;


};