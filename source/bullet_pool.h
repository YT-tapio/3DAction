#pragma once
#include"bullet.h"
#include"object_pool_base.h"


class BulletPool : public ObjectPoolBase<Bullet>
{
public:

	BulletPool();

	~BulletPool();

	/// <summary>
	/// 出るポジションと、
	/// </summary>
	void Shot(const VECTOR& pos, const VECTOR& dir);
};

