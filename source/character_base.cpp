#include<iostream>
#include"DxLib.h"
#include"character_base.h"
#include"vector_assistant.h"


CharacterBase::CharacterBase(const char* kPath, const VECTOR& pos, const VECTOR& rot,const VECTOR& scale)
	:Object3D(kPath,pos,rot,scale)
{
	
}

CharacterBase::~CharacterBase()
{
	
}

void CharacterBase::Init()
{

}

void CharacterBase::Update()
{
	Setting();
}

void CharacterBase::Draw()
{
	MV1DrawModel(handle_);
}