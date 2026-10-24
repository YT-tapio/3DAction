#pragma once

class AnimatorBase;
class Time;

class TitlePlayerController
{
public:

	TitlePlayerController();

	~TitlePlayerController();

	void Init();

	void Update();

	void Draw();

private:

	std::shared_ptr<AnimatorBase> animator_;
	std::shared_ptr<Time> time_;

	int model_handle_;



};