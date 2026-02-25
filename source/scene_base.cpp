#include<iostream>
#include"DxLib.h"
#include"scene_base.h"
#include"brain.h"

SceneBase::SceneBase()
{

}

SceneBase::~SceneBase()
{
	Brain::GetInstance().DeleteVirtualCamera();
}

void SceneBase::Init()
{

}

void SceneBase::Update()
{

}

void SceneBase::Draw()
{

}