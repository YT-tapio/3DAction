#pragma once
#include"scene_base.h"

class SkyDome;
class ButtonUI;
class VariableTimer;
class Camera;
class TitlePlayerController;
class TitleEnemyController;
class LogoController;
class StartGuide;

class Title : public SceneBase
{
public:

	Title();

	~Title() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	const std::string GetName() const override;

private:

	void ReStart();

private:

	std::shared_ptr<Camera> camera_;
	std::shared_ptr<ButtonUI> start_button_;
	std::shared_ptr<VariableTimer> offset_timer_;

	std::shared_ptr<TitlePlayerController> player_controller_;
	std::shared_ptr<TitleEnemyController> enemy_controller_;
	std::shared_ptr<LogoController> logo_controller_;
	std::shared_ptr<StartGuide> start_ui_;

	int title_logo_handle_;
	int player_handle_;
	int enemy_handle_;
	int stage_handle_;
	int sky_dome_handle_;

	bool is_push_;
	bool is_stop_;
};
