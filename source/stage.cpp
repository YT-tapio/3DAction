#include<iostream>
#include"DxLib.h"
#include"stage.h"

Stage::Stage()
	:Object3D("data/model/stage/flat_stage.mv1", VGet(0.f, -10.f, 50.f), VectorAssistant::VGetZero(), VectorAssistant::VGetSame(100.f))
{
	
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

