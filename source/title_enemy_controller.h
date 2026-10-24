#pragma once

class AnimatorBase;
class Time;

class TitleEnemyController
{
public:

	TitleEnemyController();

	~TitleEnemyController();

	void Init();

	void Update();

	void Draw();

	void Debug();

private:

	void Move();

	void Setting();

private:

	const float kDashSpeed = 0.5f;

	std::shared_ptr<AnimatorBase> animator_;
	std::shared_ptr<Time> time_;

	VECTOR pos_;
	VECTOR scale_;
	VECTOR rotation_;

	int model_handle_;

};