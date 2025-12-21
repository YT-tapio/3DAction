#include"DxLib.h"
#include"capsule.h"
#include"color.h"

Capsule::Capsule(float r,float vertical)
	: r_(r)
	, vertical_(vertical)
{

}

Capsule::~Capsule()
{

}

void Capsule::Draw(const VECTOR& pos)
{
	VECTOR start = VAdd(pos, VGet(0.f, r_, 0.f));
	VECTOR end = VAdd(start, VGet(0.f, vertical_, 0.f));

	const int kDivNum = 20;

	DrawCapsule3D(start, end, r_, kDivNum, Color::kWhite, Color::kWhite, FALSE);
}
