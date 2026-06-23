#pragma once

class SubScreen;
class ConditionTimer;

class StaminaUI : public IUIObject
{
public:

	StaminaUI(std::function<float()> get_base_stamina, std::function<float()> get_current_stamina,
		std::function<bool()> can_use_stamina);

	~StaminaUI();

	void Init() override;

	void Update() override;

	const void Draw() const override;

private:

	/// <summary>
	/// staminaのbodyに関するupdate
	/// </summary>
	void StaminaBodyUpdate();

	/// <summary>
	/// ブレンドを使うもののdraw
	/// </summary>
	const void UseBlendDraw() const;

	void LoadFile();

private:

	// スタミナを描画するscreenを用意
	std::shared_ptr<SubScreen> stamina_body_screen_;
	std::shared_ptr<ConditionTimer> disp_timer_;

	std::function<float()> get_base_stamina_;
	std::function<float()> get_current_stamina_;
	std::function<bool()> can_use_stamina_;

	// 全部の
	VECTOR base_center_pos_;	// 中心座標
	float base_scale_;					// 大きさ
	float current_blend_value_;		// 現在のブレンド量
	float target_blend_value_;		// 目標のブレンド量
	float base_blend_speed_;				// ブレンドするときの速さ

	// body
	int body_color_;
	float body_percent_;
	float body_radius_;
	float body_thickness_;

	// 背景のcolor
	int background_color_;
	int background_blend_value_;
	float background_radius_;
	
	// 枠
	int edge_color_;
	float edge_radius_;
	float edge_thickness_;

	
	


};