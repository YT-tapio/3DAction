#pragma once
#include"attack_range.h"

class AttackRangeCircle : public AttackRange
{
public:

	AttackRangeCircle();

	~AttackRangeCircle() override;

	void Active(const VECTOR& pos, const VECTOR scale, std::function<float()> ratio);

	void SetPos(const VECTOR& pos);

private:

	void LoadFile();

private:

};