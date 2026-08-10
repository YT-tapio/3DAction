#pragma once
#include"sound_base.h"

class Sound3D : public SoundBase
{
public:

	Sound3D(const std::string& file_path);

	~Sound3D();

	void Init() override;

	void SetPos(const VECTOR& pos);

private:

	void LoadFile(const std::string& file_path);

private:

	VECTOR pos_;

};