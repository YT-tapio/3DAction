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
	/// 回避に使うスタミナに関するupdate
	/// </summary>
	void AvoidStaminaUpdate();

	/// <summary>
	/// ブレンドを使うものを描画する
	/// </summary>
	const void UseBlendDraw() const;

	void LoadFile();

private:

	std::shared_ptr<SubScreen> stamina_body_screen_;	// スタミナを描画するscreenを用意
	std::shared_ptr<SubScreen> avoid_stamina_screen_;	// 回避に使うサークルを描画するscreenを用意
	std::shared_ptr<ConditionTimer> disp_timer_;

	// TODO:playerGroupから現在の操作している対象のを取得する
	std::function<float()> get_base_stamina_;					// もともとのスタミナ
	std::function<float()> get_current_stamina_;				// 現在のスタミナ
	std::function<bool()> can_use_stamina_func_;			// スタミナが使えるか
	std::function<float()> get_avoid_use_stamina_value_;	// 回避に使うスタミナ量

	// 全部の
	VECTOR base_center_pos_;	// 中心座標
	float base_scale_;					// 大きさ
	float current_blend_value_;		// 現在のブレンド量
	float target_blend_value_;		// 目標のブレンド量
	float base_blend_speed_;				// ブレンドするときの速さ

	// body
	int body_color_;
	int body_base_color_;
	float body_ratio_;
	float body_radius_;
	float body_thickness_;

	// 回避に使うスタミナの割合
	float avoid_stamina_ratio_;

	// HPが低い時に描画する丸のデータ
	int low_stamina_color_;
	float low_stamina_current_blend_value_;
	float low_stamina_target_blend_value_;
	float low_stamina_blend_speed_;
	float low_stamina_ratio_;	// このratio以下は描画する

	// 背景のcolor
	int background_color_;
	int background_blend_value_;
	float background_radius_;
	
	// 枠
	int edge_color_;
	float edge_radius_;
	float edge_thickness_;

	
	


};