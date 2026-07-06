#pragma once

class VariableTimer;

/// <summary>
/// ヒットした時のボディを赤くする
/// </summary>
class HitRedBody
{
public:

	HitRedBody(const int handle);

	~HitRedBody();

	void Init();

	void Update();

	/// <summary>
	/// 体を赤くする
	/// </summary>
	void DoRedColor();

	/// <summary>
	/// 赤くするタイミングでやる
	/// </summary>
	/// <param name=""></param>
	void Request(const ChangeMethod change_method, const float time);

private:

	// 有効時間
	std::shared_ptr<VariableTimer> validity_timer_;

	// 変化方法
	ChangeMethod change_method_;

	// オーナーのモデル
	int handle_;
	// 赤の量
	float red_ratio_;
	float target_red_ratio_;
	// 変化中
	bool is_change_;
};