#pragma once
#include"attack_range.h"

class AttackRangeRectangle : public AttackRange
{
public:

	AttackRangeRectangle();

	~AttackRangeRectangle() override;

	void Active(const VECTOR& base_pos, const VECTOR& scale, const VECTOR& dir,std::function<float()> ratio);

	void SetPos(const VECTOR& pos);

	void SetDir(const VECTOR& dir);

private:

	void LoadFile();

	/// <summary>
	/// dir‚©‚ç‰ñ“]—Ê‚ğŠ„‚èo‚·
	/// </summary>
	/// <param name="dir"></param>
	void RotToDir(const VECTOR& dir);

private:

};