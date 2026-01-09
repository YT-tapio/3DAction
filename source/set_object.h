#pragma once

class SetObject
{
public:

	SetObject(const int& handle, MATRIX* mat);

	~SetObject();

	void Update();

private:

	int handle_;
	MATRIX* mat_;
};