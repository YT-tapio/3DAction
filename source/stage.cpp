#include<iostream>
#include"DxLib.h"
#include"stage.h"

Stage::Stage()
	:Object3D("stage")
{
	LoadFile();
}

Stage::~Stage()
{

}

void Stage::Init()
{

}

void Stage::Update()
{
	Setting();
}

void Stage::Draw()
{
	MV1DrawModel(handle_);	
}

void Stage::Debug()
{

}

void Stage::LoadFile()
{
	// データの読み込みの開始




}
