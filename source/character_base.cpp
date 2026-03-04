#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"character_base.h"
#include"animator_base.h"
#include"vector_assistant.h"


CharacterBase::CharacterBase(const char* id)
	:Object3D(id)
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

void CharacterBase::Debug()
{

}