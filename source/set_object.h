#pragma once

class SetObject
{
public:

	SetObject(const int& handle, VECTOR* pos,VECTOR* rot,VECTOR* scale);

	~SetObject();

	void Update();

private:

	int handle_;
	VECTOR* pos_;
	VECTOR* rot_;
	VECTOR* scale_;
};