#include<iostream>
#include"DxLib.h"
#include"stage.h"
#include"rigid_body.h"
#include"mesh.h"
#include"physics.h"

Stage::Stage()
	:Object3D("stage")
{
	LoadFile();
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Mesh>(handle_),&pos_);
}

Stage::~Stage()
{

}

void Stage::Init()
{
	rigid_body_->Init(weak_from_this());
	// RigidBodyの登録
	Physics::GetInstance().AddBody(rigid_body_);
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

void Stage::OnHit(std::shared_ptr<IHit> object)
{

}


void Stage::LoadFile()
{
	// データの読み込みの開始




}
