#include<string>
#include<memory>
#include<vector>
#include"DxLib.h"
#include"sound_manager.h"
#include"sound_2D.h"
#include"sound_3D.h"
#include<fstream>
#include<sstream>
#include"csv_file_assistant.h"

void SoundManager::Load()
{
	Load2DSound();
	// セッティング
	Set3DSoundOneMetre(1.f);
	SetCreate3DSoundFlag(TRUE);
	Load3DSound();
	SetCreate3DSoundFlag(FALSE);
}

void SoundManager::End()
{
	sound_2ds_.clear();
	sound_3ds_.clear();
}



void SoundManager::Play2DSound(const std::string& name)
{
	for (auto& sound : sound_2ds_)
	{
		if (sound->GetName() == name)
		{
			sound->Play();
		}
	}
}

void SoundManager::Play3DSound(const std::string& name)
{
	for (auto& sound : sound_3ds_)
	{
		if (sound->GetName() == name)
		{
			sound->Play();
		}
	}
}

void SoundManager::Stop(const std::string& name)
{
	for (auto& sound : sound_2ds_)
	{
		if (name == sound->GetName())
		{
			sound->Stop();
			break;
		}
	}
	for (auto& sound : sound_3ds_)
	{
		if (name == sound->GetName())
		{
			sound->Stop();
			break;
		}
	}
}

void SoundManager::AllStop()
{
	for (auto& sound : sound_3ds_)
	{
		sound->Stop();
	}
}

void SoundManager::SetPos(const std::string& name, const VECTOR& pos)
{
	for (auto& sound : sound_3ds_)
	{
		if (sound->GetName() == name)
		{
			sound->SetPos(pos);
		}
	}
}

SoundManager::SoundManager()
{

}

void SoundManager::Load2DSound()
{
	std::ifstream file("data/csv/sound/2D/2D_sound_datas.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の行を飛ばす
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう
		sound_2ds_.push_back(std::make_shared<Sound2D>(CSVFileAssistant::GetStringOfCSVFile(ss, data)));
	}
	
}

void SoundManager::Load3DSound()
{
	std::ifstream file("data/csv/sound/3D/3D_sound_datas.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の行を飛ばす
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう
		sound_3ds_.push_back(std::make_shared<Sound3D>(CSVFileAssistant::GetStringOfCSVFile(ss, data)));
	}
}