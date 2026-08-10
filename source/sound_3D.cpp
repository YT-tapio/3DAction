#include<string>
#include"DxLib.h"
#include"sound_3D.h"

Sound3D::Sound3D(const std::string& file_path)
{
	LoadFile(file_path);
}

Sound3D::~Sound3D()
{

}

void Sound3D::Init()
{

}

void Sound3D::SetPos(const VECTOR& pos)
{
	pos_ = pos;
	// 
	Set3DPositionSoundMem(pos_, handle_);
}

void Sound3D::LoadFile(const std::string& file_path)
{



}
