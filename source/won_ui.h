#pragma once
#include"enemy_observer_interface.h"

class ConditionTimer;

class WonUI : public IEnemyObserver
{
public:

	WonUI();

	~WonUI();

	void Init();

	void Update();

	void Draw();

	void OnEnemyDeath() override;

private:

	void LoadFile();

	void DrawBackGround();

	void DrawWonImage();

	/// <summary>
	/// ‰ñ”ğ‚É¬Œ÷‚µ‚½”
	/// </summary>
	void DrawAvoidCollectNum();

	/// <summary>
	/// “G‚ªó‚¯‚½Å‘åƒ_ƒ[ƒW‚ğ•`‰æ
	/// </summary>
	void DrawMostTakeDamageEnemy();

private:

	std::shared_ptr<ConditionTimer> timer_;

	VECTOR base_pos_;
	VECTOR back_ground_size_;	// ”wŒi‚Ì‘å‚«‚³

	VECTOR won_image_pos_;
	
	int won_image_handle_;

	float base_size_;			// ‚à‚Æ‚à‚Æ‚Ì‘å‚«‚³
	float base_blend_num_;		// ‚à‚Æ‚à‚Æ‚ÌƒuƒŒƒ“ƒh—¦
	
	float target_back_ground_blend_num_;
	float current_back_ground_blend_num_;// 
	float back_ground_blend_speed_;
	
	float won_image_size_;
	float won_image_rot_;

	bool is_active_;

};