#pragma once

class SceneManager;

class Application
{
public:

	Application();

	~Application();

	void Update();

private:

	std::shared_ptr<SceneManager> scene_manager_;

};