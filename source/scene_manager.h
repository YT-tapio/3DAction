#pragma once

class SceneBase;
class FPS;

class SceneManager
{
public:

	SceneManager();

	~SceneManager();

	void Update();

private:

	std::shared_ptr<SceneBase> scene_;
};