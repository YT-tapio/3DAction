#include<string>
#include"object_base.h"
#include"object_2d.h"

Object2D::Object2D(const std::string path)
	: ObjectBase()
{
	handle_ = LoadGraph(path.c_str());
	if (handle_ == -1) { printfDx("2DÅFì«Ç›çûÇ›ÉGÉâÅ[\n"); }
}

Object2D::~Object2D()
{
	DeleteGraph(handle_);
}

void Object2D::Init()
{

}

void Object2D::Update()
{

}

void Object2D::Draw()
{

}

void Object2D::Debug()
{
	DrawRotaGraph(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y), 1, 0, handle_, TRUE, FALSE);
}
