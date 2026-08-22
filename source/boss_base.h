#pragma once
#include"status_holder_interface.h"
#include"enemy_base.h"

class BossBase : public EnemyBase
{
public:

	BossBase(const VECTOR& pos, bool* game_start);

	virtual ~BossBase() override;

	virtual void Init() override;


protected:

	virtual void LoadFile() override;

private:


};
