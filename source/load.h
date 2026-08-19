#pragma once
#include"scene_base.h"

class Load : public SceneBase
{
public:
	
	Load(const std::string& next_scene);

	~Load() override;

	void Update() override;

private:

	std::string next_scene_;

};