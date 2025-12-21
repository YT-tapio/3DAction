#include"DxLib.h"
#include"sphere.h"
#include"color.h"

Sphere::Sphere(float r)
	: r_(r)
{

}

Sphere::~Sphere()
{

}

void Sphere::Draw(const VECTOR& pos)
{
	const int kDivNum = 20;

	DrawSphere3D(pos, r_, kDivNum, Color::kWhite, Color::kWhite, FALSE);
}
