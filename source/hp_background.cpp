#include<string>
#include<functional>
#include"DxLib.h"
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"hp_background.h"
#include"draw_2D.h"

HPBackGround::HPBackGround(const ImageData& data, const VECTOR& pos, float size_rate, float rot)
	: Object2D(data,pos,size_rate,rot)
{
	
}

HPBackGround::~HPBackGround()
{

}

void HPBackGround::Init()
{

}

void HPBackGround::Update()
{

}

void HPBackGround::Draw()
{
	std::function<void()> draw = [this]()-> void { Object2D::Draw(); };
	Draw2D::Blend(draw, 180);
}

void HPBackGround::Debug()
{

}