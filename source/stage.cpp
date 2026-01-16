#include<iostream>
#include"DxLib.h"
#include"stage.h"
#include"rigid_body.h"
#include"mesh.h"
#include"physics.h"
#include"object_setter.h"
#include"debug.h"
#include"color.h"

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
	scale_ = VectorAssistant::VGetSame(0.1f);
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Mesh>(handle_), &pos_, FALSE, TRUE, 20.f);
}

Stage::~Stage()
{

}

void Stage::Init()
{
	rigid_body_->Init(weak_from_this());
	// RigidBodyの登録
	Physics::GetInstance().AddBody(rigid_body_);
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
}

void Stage::Update()
{
	Setting();
}

void Stage::Draw()
{
	DrawSphere3D(pos_, 0.01f, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	MV1DrawModel(handle_);
}

void Stage::Debug()
{
	DrawString(0, Debug::GetInstance().GetNowLineSize(), "----------stage-----------", Color::kWhite);
	Debug::GetInstance().Add();

	DrawString(0, Debug::GetInstance().GetNowLineSize(), "pos", Color::kWhite);
	Debug::GetInstance().Add();
	DrawFormatString(0, Debug::GetInstance().GetNowLineSize(), Color::kWhite, "x : %.2f, y : %.2f, z : %.2f", pos_.x, pos_.y, pos_.z);
	Debug::GetInstance().Add();
}

void Stage::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}


void Stage::LoadFile()
{
	// データの読み込みの開始




}
