#pragma once

class ConditionTimer;

class GameStartTimer
{
public:

	GameStartTimer();

	~GameStartTimer();

	void Init();

	void Update();

private:

	std::shared_ptr<ConditionTimer> timer_;

	// タイマーと処理の終了
	bool end_;


};