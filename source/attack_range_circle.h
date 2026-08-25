#pragma once
#include"attack_range.h"

class AttackRangeCircle : public AttackRange
{
public:

	AttackRangeCircle();

	~AttackRangeCircle() override;

	void Update() override;

	void Active(const VECTOR& pos, const VECTOR scale, const float& time);

	void SetPos(const VECTOR& pos);

private:

	void LoadFile();

private:

};