#pragma once
#include"collider_name.h"

class ColliderBase
{
public:

	ColliderBase(ColliderName name);

	virtual ~ColliderBase();

	virtual void Draw(const VECTOR& pos);

	const ColliderName GetName() const;

private:

	ColliderName name_;

};