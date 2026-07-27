#pragma once
#include"scene_base.h"

class Title : public SceneBase
{
public:

	Title();

	~Title() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	const std::string GetName() const override;

private:

	

	
};
