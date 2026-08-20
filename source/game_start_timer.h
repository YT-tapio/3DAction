#pragma once

class ConditionTimer;

class GameStartTimer
{
public:

	GameStartTimer(bool* game_start);

	~GameStartTimer();

	void Init();

	void Update();

	void Draw();

private:

	void DrawGame();

	void DrawStart();

private:

	std::shared_ptr<ConditionTimer> timer_;

	VECTOR game_image_pos_;
	VECTOR start_image_pos_;

	int game_handle_;
	int start_handle_;

	float blend_;
	float start_blend_;

	float draw_start_;

	// タイマーと処理の終了
	bool end_;
	bool* game_start_;

};