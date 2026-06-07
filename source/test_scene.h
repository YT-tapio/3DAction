#pragma once
#include"scene_base.h"

class Test : public SceneBase
{
public:

	Test();

	~Test();

	void Init() override;

	void Update() override;

	void Draw() override;

	const std::string GetName() const override;

private:




};
