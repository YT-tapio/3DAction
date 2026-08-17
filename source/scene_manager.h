#pragma once

class SceneBase;
class FPS;

class SceneManager
{
public:

	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

	void Update();

	bool LoadScene(const std::string& next_scene);

	void End();

private:

	SceneManager();

private:

	std::shared_ptr<SceneBase> scene_;

	bool is_change_;
};