#include<string>
#include"DxLib.h"
#include"play_sound.h"
#include<vector>
#include<memory>
#include"sound_manager.h"
#include"behavior_status.h"

PlaySound3D::PlaySound3D(std::weak_ptr<ObjectBase> owner,VECTOR* pos, const std::string& name)
	: BehaviorBase(owner)
	, pos_(pos)
	, name_(name)
{

}

PlaySound3D::~PlaySound3D()
{

}

void PlaySound3D::Init()
{

}

void PlaySound3D::Entry()
{
	SoundManager::GetInstance().Play3DSound(name_);
	SoundManager::GetInstance().SetPos(name_,*pos_);
}

BehaviorStatus PlaySound3D::Update()
{
	return BehaviorStatus::kComplete;
}

void PlaySound3D::Exit()
{

}