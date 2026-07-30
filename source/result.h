#pragma once

#include"scene_base.h"

class Result :public SceneBase
{
public:

	Result();

	~Result() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	const std::string GetName() const override;

private:


};