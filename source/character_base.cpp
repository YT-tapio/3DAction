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
	is_invincible_ = FALSE;
}

CharacterBase::~CharacterBase()
{
	
}

void CharacterBase::Init()
{
	is_invincible_ = FALSE;
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

void CharacterBase::SetInvincible(bool flag)
{
	is_invincible_ = flag;
}

void CharacterBase::Teleport(const VECTOR& pos)
{
	pos_ = pos;
}

const VECTOR CharacterBase::GetAtackTargetPos() const
{
	// ëŒè€ÇéÊìæ


	return VGet(0, 0, 0);
}

const bool CharacterBase::GetIsInvincible() const
{
	return is_invincible_;
}

std::shared_ptr<AnimatorBase> CharacterBase::GetAnimator()
{
	return animator_;
}