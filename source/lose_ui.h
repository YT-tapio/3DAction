#pragma once
#include"player_observer_interface.h"

class ButtonUI;

class LoseUI : public IPlayerObserver
{
public:

	LoseUI();

	~LoseUI();

	void Init();

	void Update();

	void Draw();

	void OnPlayerDeath() override;

private:

	void LoadFile();

	void DrawBackGround();

	void DrawGameOver();

	void DrawButton();

private:

	std::shared_ptr<ButtonUI> retry_button_;
	std::shared_ptr<ButtonUI> go_title_button_;

	VECTOR back_ground_pos_;
	VECTOR game_over_pos_;

	VECTOR retry_ui_pos_;
	VECTOR go_title_ui_pos_;

	VECTOR offset_;

	int game_over_handle_;
	int Abutton_image_handle_;
	int Bbutton_image_handle_;
	int font_handle_;

	int body_color_;
	int edge_color_;

	float target_blend_num_;
	float current_blend_num_;

	float current_game_over_blend_num_;	
	float current_button_blend_num_;

	bool is_active_;
};