#pragma once
#include"sound_base.h"

class Sound2D : public SoundBase
{
public:

	Sound2D(const std::string& file_path);

	~Sound2D() override;

	void Init() override;

private:

	void LoadFile(const std::string& file_path);

};