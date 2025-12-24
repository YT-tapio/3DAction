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

	handle_ = MV1LoadModel("data/model/stage/flat_stage.mv1");

	if (handle_ == -1)
	{
		printfDx("読み込みできない\n");
	}
	pos_ = VGet(0.f, -10.f, 30.f);
	scale_ = VectorAssistant::VGetSame(15.f);
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Mesh>(handle_),nullptr,&pos_,FALSE,20.f);
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
	DrawSphere3D(pos_, 1.f, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	MV1DrawModel(handle_);	
}

void Stage::Debug()
{

}

void Stage::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}


void Stage::LoadFile()
{
	// データの読み込みの開始




}
