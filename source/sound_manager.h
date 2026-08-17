#pragma once

class Sound2D;
class Sound3D;

class SoundManager
{
public:

	static SoundManager& GetInstance()
	{
		static SoundManager instance;
		return instance;
	}

	void Load();

	void End();

	void AllStop();
	
	void Play2DSound(const std::string& name);

	void Play3DSound(const std::string& name);

	void SetPos(const std::string& name,const VECTOR& pos);

private:

	SoundManager();

	void Load2DSound();

	void Load3DSound();

private:

	std::vector<std::shared_ptr<Sound3D>> sound_3ds_;
	std::vector<std::shared_ptr<Sound2D>> sound_2ds_;

};