#pragma once
#include"scene_base.h"
#include<vector>

class Camera;
class ObjectBase;

class Game : public SceneBase
{
public:

	Game();

	~Game() override;

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	std::shared_ptr<Camera> camera_;
	std::vector<std::shared_ptr<ObjectBase>> objects_;
};