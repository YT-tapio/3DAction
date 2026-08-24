#pragma once
#include"attack_range.h"

class AttackRangeRectangle : public AttackRange
{
public:

	AttackRangeRectangle();

	~AttackRangeRectangle() override;

	void Active(const VECTOR& pos, const VECTOR& scale) override;

private:

	void LoadFile();

private:

};