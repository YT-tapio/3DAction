#pragma once

class ConditionTimer;

class GameStartTimer
{
public:

	GameStartTimer(bool* game_start);

	~GameStartTimer();

	void Init();

	void Update();

private:

	std::shared_ptr<ConditionTimer> timer_;

	// タイマーと処理の終了
	bool end_;
	bool* game_start_;

};