#pragma once
#include"effect_data.h"

class EffectBase
{
public:

	EffectBase(std::string data_file_path);

	~EffectBase();

	void Init();

	void Update();

	void Play();

	void Stop();

	void RePlay();

	void Draw();

	void Debug();

	
protected:

	EffectData data_;

	bool is_play_;
	bool is_stop_;

private:

	void LoadFile();

	std::string data_file_path_;

};