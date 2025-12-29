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

	VECTOR capsule_pos = VGet(-10, 0, 20);
	float vertical = 10.f;
	float capsule_r = 5.f;

	VECTOR capsule2_pos = VGet(10, 0, 20);
	float capsule2_vertical = 10.f;
	float capsule2_r = 3.f;

	std::shared_ptr<Camera> camera_;
	std::vector<std::shared_ptr<ObjectBase>> objects_;
};