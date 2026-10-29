#pragma once

class ConditionTimer;

class LogoController
{
public:

	LogoController();

	~LogoController();

	void Awake();

	void Init();

	void Update();

	void Draw();

	void Active();

private:

	const float kTargetSize = 0.7f;

	std::shared_ptr<ConditionTimer> size_up_timer_;

	VECTOR pos_;


	int handle_;
	float size_;

	bool is_active_;


};