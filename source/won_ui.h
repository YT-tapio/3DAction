#pragma once
#include"enemy_observer_interface.h"
#include"player_observer_interface.h"

class ConditionTimer;

class WonUI : public IEnemyObserver , public IPlayerObserver
{
public:

	WonUI();

	~WonUI();

	void Init();

	void Update();

	void Draw();

	void OnTakeDamage(const float& damage);

	void OnEnemyDeath() override;

	void OnPlayerJustAvoid() override;

	void OnPlayerAvoidCollect() override;

private:

	void LoadFile();

	void DrawBackGround();

	void DrawWonImage();

	/// <summary>
	/// 回避に成功した数
	/// </summary>
	void DrawAvoidCollectNum();

	/// <summary>
	/// 敵が受けた最大ダメージを描画
	/// </summary>
	void DrawMostTakeDamageEnemy();

	void DrawGameToNext();

private:

	struct FontData
	{
		int handle;
		int body_color;
		int edge_color;
	};

	std::shared_ptr<ConditionTimer> timer_;

	VECTOR base_pos_;
	VECTOR back_ground_size_;	// 背景の大きさ

	VECTOR won_image_pos_;		//
	VECTOR avoid_collect_pos_;	// 
	VECTOR most_damage_pos_;	//

	VECTOR retry_ui_pos_;
	VECTOR go_title_ui_pos_;

	VECTOR offset_;

	VECTOR offset_button_pos_;

	FontData avoid_collect_font_;
	FontData most_damage_font_;
	FontData go_next_scene_font_;

	int won_image_handle_;

	int Abutton_image_handle_;
	int Bbutton_image_handle_;

	int just_avoid_num_;
	int avoid_collect_num_;

	float enemy_take_most_damage_;	// 敵が受けた最大のダメージ

	float base_size_;			// もともとの大きさ
	float base_blend_num_;		// もともとのブレンド率

	float target_back_ground_blend_num_;
	float current_back_ground_blend_num_;// 
	float back_ground_blend_speed_;
	
	float won_image_size_;
	float won_image_rot_;

	bool is_active_;
	bool is_play_;
};