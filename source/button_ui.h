#pragma once

class ButtonUI
{
public:

	ButtonUI(const std::string& name, std::function<void()> execute);

	~ButtonUI();

	void Init();

	void Update();

	void Draw();

private:

	virtual bool CheckMyButton();

private:

	VECTOR pos_;

	std::function<void()> execute_;
	std::string name_;

	int handle_;	// 自分の操作に対応しているボタンを画像ハンドルとして保持

	float default_size_;
	float current_size_;
	float target_size_;

	bool is_execute_;
};