#include<string>
#include"object_3D.h"
#include"skydome.h"
#include"object_setter.h"
#include"vector_assistant.h"

SkyDome::SkyDome()
	: Object3D("skydome")
{
	const std::string model_path = "data/model/skydome/SkyDome.mv1";
	handle_ = MV1LoadModel(model_path.c_str());
	if (handle_ == -1) { printfDx("ì«Ç›çûÇ›é∏îs\n"); }
	scale_ = VectorAssistant::VGetSame(200.f);
	ObjectSetter::GetInstance().AddResource(handle_,&pos_, &rot_, &scale_);
}

SkyDome::~SkyDome()
{
	
}

void SkyDome::Init()
{

}

void SkyDome::Update()
{

}

void SkyDome::Draw()
{
	MV1DrawModel(handle_);
}

void SkyDome::Debug()
{

}