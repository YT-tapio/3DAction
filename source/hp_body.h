#pragma once

class SubScreen;

class HPBody : public Object2D
{
public:
	
	HPBody(const ImageData& data, const VECTOR& pos, float size_rate, float rot
		, std::function<int()> get_base_hp_, std::function<int()> get_current_hp_);

	~HPBody() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

private:

	/// <summary>
	/// screenを起動して描画を行う
	/// </summary>
	void SetUpScreen();

private:

	static constexpr float kMaxFlashValue = 50.f;
	static constexpr float kMinFlashValue = 0.f;

	static constexpr float kFlashSpeed = 2.3f;

	// 関数ポインタでhpを取得する
	std::function<int()> get_base_hp_;
	std::function<int()> get_current_hp_;

	// このscreenに描画する
	std::shared_ptr<SubScreen> screen_;

	VECTOR blind_box_pos_;

	// 点滅する際のひかりのつよさ　
	float flash_value_;
	float target_flash_value_;

	float now_ratio_;
	// bodyを隠すためのboxの大きさ
	float blind_width_;
	float blind_height_;

	// 点滅の際に白くなるか
	bool flash_up_;
	bool red_flash_;
};