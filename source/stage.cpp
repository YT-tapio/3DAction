#include<iostream>
#include<memory>
#include<string>
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

	handle_ = MV1LoadModel("data/model/stage/field.mv1");
	// 当たり判定用モデル
	coll_handle_ = MV1LoadModel("data/model/stage/stage_field_test.mv1");
	
	if (handle_ == -1)
	{
		printfDx("読み込みできない\n");
	}
	if (coll_handle_ == -1)
	{
		printfDx("読み込みできない\n");
	}
	pos_ = VGet(0.f, -20.f, 30.f);
	scale_ = VectorAssistant::VGetSame(0.3f);
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Mesh>(coll_handle_), &pos_, FALSE, TRUE, 20.f,1.f);
}

Stage::~Stage()
{
	MV1DeleteModel(coll_handle_);
}

void Stage::Init()
{
	rigid_body_->Init(weak_from_this());
	rigid_body_->SetTag("stage");
	// RigidBodyの登録
	Physics::GetInstance().AddBody(rigid_body_);
	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
	ObjectSetter::GetInstance().AddResource(coll_handle_, &pos_, &rot_, &scale_);
}

void Stage::Update()
{
	//Setting();
}

void Stage::Draw()
{
	SetUseLighting(FALSE);
	MV1DrawModel(handle_);
	SetUseLighting(TRUE);
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

std::shared_ptr<RigidBody> Stage::GetRigidBody()
{
	return rigid_body_;
}