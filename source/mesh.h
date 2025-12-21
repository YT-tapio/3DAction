#pragma once
#include"collider_base.h"

class Mesh :public ColliderBase
{
public:

	Mesh(int handle);

	~Mesh() override;

	void Draw(const VECTOR& pos)override;

	const int GetHandle() const;

private:

	int handle_;

};
