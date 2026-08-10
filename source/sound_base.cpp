#include<string>
#include"DxLib.h"
#include"sound_base.h"

SoundBase::SoundBase()
{

}

SoundBase::~SoundBase()
{
	DeleteSoundMem(handle_);
}

void SoundBase::Init()
{

}

void SoundBase::Update()
{

}

void SoundBase::Play()
{
	PlaySoundMem(handle_, DX_PLAYTYPE_BACK);
}

void SoundBase::Stop()
{
	StopSoundMem(handle_);
}

const std::string SoundBase::GetName() const
{
	return name_;
}